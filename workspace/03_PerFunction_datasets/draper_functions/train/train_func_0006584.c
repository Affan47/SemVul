trx_write_serialisation_history(

	trx_t*		trx)
{
	mtr_t		mtr;
	trx_rseg_t*	rseg;
	trx_sysf_t*	sys_header = NULL;

	ut_ad(!mutex_own(&kernel_mutex));

	rseg = trx->rseg;

	mtr_start(&mtr);


	if (trx->update_undo != NULL) {
		page_t*		undo_hdr_page;
		trx_undo_t*	undo = trx->update_undo;


		mutex_enter(&rseg->mutex);


		trx_serialisation_number_get(trx);


		undo_hdr_page = trx_undo_set_state_at_finish(undo, &mtr);

		trx_undo_update_cleanup(trx, undo_hdr_page, &mtr);
	} else {
		mutex_enter(&rseg->mutex);
	}

	if (trx->insert_undo != NULL) {
		trx_undo_set_state_at_finish(trx->insert_undo, &mtr);
	}

	mutex_exit(&rseg->mutex);


	if (trx->mysql_log_file_name
	    && trx->mysql_log_file_name[0] != '\0') {
		if (!sys_header) {
			sys_header = trx_sysf_get(&mtr);
		}

		trx_sys_update_mysql_binlog_offset(
			sys_header,
			trx->mysql_log_file_name,
			trx->mysql_log_offset,
			TRX_SYS_MYSQL_LOG_INFO, &mtr);

		trx->mysql_log_file_name = NULL;
	}

	if (trx->mysql_master_log_file_name[0] != '\0') {

		if (!sys_header) {
			sys_header = trx_sysf_get(&mtr);
		}

		trx_sys_update_mysql_binlog_offset(
			sys_header,
			trx->mysql_master_log_file_name,
			trx->mysql_master_log_pos,
			TRX_SYS_MYSQL_MASTER_LOG_INFO, &mtr);
		trx->mysql_master_log_file_name = "";
	}

	if (trx->css_mysql_master_log_file_name[0] != '\0') {

		if (!sys_header) {
			sys_header = trx_sysf_get(&mtr);
		}

		trx_sys_update_mysql_binlog_offset(
			sys_header,
			trx->css_mysql_relay_log_file_name,
			trx->css_mysql_relay_log_pos,
			TRX_SYS_CSS_COMMIT_RELAY_LOG_INFO, &mtr);

		trx_sys_update_mysql_binlog_offset(
			sys_header,
			trx->css_mysql_master_log_file_name,
			trx->css_mysql_master_log_pos,
			TRX_SYS_CSS_COMMIT_MASTER_LOG_INFO, &mtr);

		trx_sys_update_mysql_binlog_offset(
			sys_header,
			trx->css_mysql_relay_log_file_name,
			trx->css_mysql_relay_log_pos,
			TRX_SYS_CSS_MYSQL_RELAY_LOG_INFO, &mtr);

		trx_sys_update_mysql_binlog_offset(
			sys_header,
			trx->css_mysql_master_log_file_name,
			trx->css_mysql_master_log_pos,
			TRX_SYS_CSS_MYSQL_MASTER_LOG_INFO, &mtr);

		trx->css_mysql_master_log_file_name = "";
	}


	mtr_commit(&mtr);


	return(mtr.end_lsn);
}
