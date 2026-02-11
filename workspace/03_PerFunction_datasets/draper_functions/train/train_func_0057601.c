trx_sys_print_committed_mysql_master_log_pos(void)

{
	trx_sysf_t*	sys_header;
	mtr_t		mtr;

	mtr_start(&mtr);

	sys_header = trx_sysf_get(&mtr);

	if (mach_read_from_4(sys_header + TRX_SYS_CSS_COMMIT_MASTER_LOG_INFO
			     + TRX_SYS_MYSQL_LOG_MAGIC_N_FLD)
	    != TRX_SYS_MYSQL_LOG_MAGIC_N) {

		mtr_commit(&mtr);

		return;
	}


	trx_sys_read_log_pos(sys_header, TRX_SYS_CSS_COMMIT_MASTER_LOG_INFO,
			     trx_sys_css_mysql_master_log_name,
			     &trx_sys_css_mysql_master_log_pos);

	trx_sys_read_log_pos(sys_header, TRX_SYS_CSS_COMMIT_RELAY_LOG_INFO,
			     trx_sys_css_mysql_relay_log_name,
			     &trx_sys_css_mysql_relay_log_pos);

	mtr_commit(&mtr);

	fprintf(stderr,
		"InnoDB: In a MySQL replication slave the last"
		" master binlog file\n"
		"InnoDB: position %llu, file name %s\n",
		trx_sys_css_mysql_master_log_pos,
		trx_sys_css_mysql_master_log_name);

	fprintf(stderr,
		"InnoDB: and relay log file\n"
		"InnoDB: position %llu, file name %s\n",
		trx_sys_css_mysql_relay_log_pos,
		trx_sys_css_mysql_relay_log_name);
}
