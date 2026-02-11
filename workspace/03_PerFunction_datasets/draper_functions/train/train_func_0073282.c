nes_destroy_qp(struct ib_qp *ibqp)
{
	struct nes_qp *nesqp = to_nesqp(ibqp);
	struct nes_ucontext *nes_ucontext;
	struct ib_qp_attr attr;
	struct iw_cm_id *cm_id;
	struct iw_cm_event cm_event;
	int ret = 0;

	atomic_inc(&sw_qps_destroyed);
	nesqp->destroyed = 1;


	if (nesqp->ibqp_state >= IB_QPS_INIT && nesqp->ibqp_state <= IB_QPS_RTS) {

		attr.qp_state = IB_QPS_ERR;
		nes_modify_qp(&nesqp->ibqp, &attr, IB_QP_STATE, NULL);
	}

	if (((nesqp->ibqp_state == IB_QPS_INIT) ||
			(nesqp->ibqp_state == IB_QPS_RTR)) && (nesqp->cm_id)) {
		cm_id = nesqp->cm_id;
		cm_event.event = IW_CM_EVENT_CONNECT_REPLY;
		cm_event.status = -ETIMEDOUT;
		cm_event.local_addr = cm_id->local_addr;
		cm_event.remote_addr = cm_id->remote_addr;
		cm_event.private_data = NULL;
		cm_event.private_data_len = 0;

		nes_debug(NES_DBG_QP, "Generating a CM Timeout Event for "
				"QP%u. cm_id = %p, refcount = %u. \n",
				nesqp->hwqp.qp_id, cm_id, atomic_read(&nesqp->refcount));

		cm_id->rem_ref(cm_id);
		ret = cm_id->event_handler(cm_id, &cm_event);
		if (ret)
			nes_debug(NES_DBG_QP, "OFA CM event_handler returned, ret=%d\n", ret);
	}

	if (nesqp->user_mode) {
		if ((ibqp->uobject)&&(ibqp->uobject->context)) {
			nes_ucontext = to_nesucontext(ibqp->uobject->context);
			clear_bit(nesqp->mmap_sq_db_index, nes_ucontext->allocated_wqs);
			nes_ucontext->mmap_nesqp[nesqp->mmap_sq_db_index] = NULL;
			if (nes_ucontext->first_free_wq > nesqp->mmap_sq_db_index) {
				nes_ucontext->first_free_wq = nesqp->mmap_sq_db_index;
			}
		}
		if (nesqp->pbl_pbase && nesqp->sq_kmapped) {
			nesqp->sq_kmapped = 0;
			kunmap(nesqp->page);
		}
	} else {

		if (nesqp->nesscq)
			nes_clean_cq(nesqp, nesqp->nesscq);

		if ((nesqp->nesrcq) && (nesqp->nesrcq != nesqp->nesscq))
			nes_clean_cq(nesqp, nesqp->nesrcq);
	}
	nes_rem_ref(&nesqp->ibqp);
	return 0;
}
