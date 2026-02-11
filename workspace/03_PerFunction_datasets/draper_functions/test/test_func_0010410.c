on_op_done(lrmd_rsc_t* rsc, lrmd_op_t* op)
{
	int rc = HA_OK;
	int target_rc, last_rc, op_rc;
	int rc_changed;
	op_status_t op_status;

	LRMAUDIT();
	CHECK_ALLOCATED(op, "op", HA_FAIL );
	if (op->exec_pid == 0) {
		lrmd_log(LOG_ERR, "%s: op->exec_pid == 0",__FUNCTION__);
		return HA_FAIL;
	}
	op->t_done = time_longclock();

	if (debug_level >= 2) {
		lrmd_debug(LOG_DEBUG, "%s: %s",__FUNCTION__, op_info(op));
		lrmd_op_dump(op, __FUNCTION__);
	}

	return_on_no_int_value(op->msg,F_LRM_TARGETRC,&target_rc);
	return_on_no_int_value(op->msg,F_LRM_OPSTATUS,(int *)&op_status);

	last_rc = op_rc = -1;
	ha_msg_value_int(op->msg,F_LRM_RC,&op_rc);
	ha_msg_value_int(op->msg,F_LRM_LASTRC,&last_rc);
	rc_changed = (
		op_status == LRM_OP_DONE
		&& op_rc != -1
		&& ((last_rc == -1) || (last_rc != op_rc))
	);
	if (rc_changed) {
		if (HA_OK != ha_msg_mod_int(op->msg, F_LRM_LASTRC, op_rc)) {
			lrmd_log(LOG_ERR,"%s: cannot save status to msg",__FUNCTION__);
			return HA_FAIL;
		}
		op->t_rcchange = op->t_perform;
	}
	if (store_timestamps(op))
		return HA_FAIL;


	rsc->op_list = g_list_remove(rsc->op_list,op);
	lrmd_debug2(LOG_DEBUG
	, 	"%s:%s is removed from op list"
	,	__FUNCTION__, op_info(op));

	if (!op->is_cancelled) {
		if( !record_op_completion(rsc,op) ) {
			if (op->interval)
				to_repeatlist(rsc,op);
		}
	} else {
		if (HA_OK != ha_msg_mod_int(op->msg,F_LRM_OPSTATUS,(int)LRM_OP_CANCELLED)) {
			LOG_FAILED_TO_ADD_FIELD(F_LRM_OPSTATUS);
			return HA_FAIL;
		}
		op_status = LRM_OP_CANCELLED;
		remove_op_history(op);
	}

	if (rsc_removal_pending(rsc)) {
		if (HA_OK != ha_msg_add_int(op->msg,F_LRM_RSCDELETED,1)) {
			LOG_FAILED_TO_ADD_FIELD(F_LRM_RSCDELETED);
		}
	}
	if (op_status != LRM_OP_DONE
		|| (op_rc == -1)
		|| (op_rc == target_rc)
		|| (target_rc == EVERYTIME)
		|| ((target_rc == CHANGED) && rc_changed)
		|| rsc_removal_pending(rsc)
	) {
		notify_client(op);
	}
	lrmd_op_destroy(op);
	if( !rsc->op_list ) {
		if( rsc_removal_pending(rsc) ) {
			lrmd_log(LOG_INFO, "late removal of resource %s", rsc->id);
			lrmd_rsc_destroy(rsc);
			rc = -1;
		} else {
			rsc_reset_state(rsc);
		}
	}
	LRMAUDIT();
	if (shutdown_in_progress && can_shutdown()) {
		lrm_shutdown();
	}
	return rc;
}
