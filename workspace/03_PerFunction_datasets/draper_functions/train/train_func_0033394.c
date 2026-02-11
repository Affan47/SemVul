syb_st_finish(SV *sth, imp_sth_t *imp_sth) {
	dTHX;
	D_imp_dbh_from_sth;
	CS_CONNECTION *connection;

	if (imp_sth->bcp_desc) {
		return sth_blk_finish(imp_dbh, imp_sth, sth);
	}

	connection = imp_sth->connection ? imp_sth->connection
			: imp_dbh->connection;


	if (imp_dbh->flushFinish) {
		if (DBIc_DBISTATE(imp_dbh)->debug >= 3)
			PerlIO_printf(DBIc_LOGPIO(imp_dbh),
					"    syb_st_finish() -> flushing\n");
		DBIh_CLEAR_ERROR(imp_sth);
		while (DBIc_ACTIVE(imp_sth) && !imp_dbh->isDead && imp_sth->exec_done
				&& !SvTRUE(DBIc_ERR(imp_sth))) {
			AV *retval;
			do {
				retval = syb_st_fetch(sth, imp_sth);
			} while (retval && retval != Nullav);
		}
	} else {
		if (DBIc_ACTIVE(imp_sth)) {
#if defined(ROGUE)
			if(DBIc_DBISTATE(imp_dbh)->debug >= 3)
			PerlIO_printf(DBIc_LOGPIO(imp_dbh), "    syb_st_finish() -> ct_cancel(CS_CANCEL_CURRENT)\n");
			if(ct_cancel(NULL, imp_sth->cmd, CS_CANCEL_CURRENT) == CS_FAIL) {
				ct_close(connection, CS_FORCE_CLOSE);
				imp_dbh->isDead = 1;
			}
#else
			if (DBIc_DBISTATE(imp_dbh)->debug >= 3)
				PerlIO_printf(DBIc_LOGPIO(imp_dbh),
						"    syb_st_finish() -> ct_cancel(CS_CANCEL_ALL)\n");
			if (ct_cancel(connection, NULL, CS_CANCEL_ALL) == CS_FAIL) {
				ct_close(connection, CS_FORCE_CLOSE);
				imp_dbh->isDead = 1;
			}
#endif
		}
	}
	clear_sth_flags(sth, imp_sth);
	DBIc_ACTIVE_off(imp_sth);
	return 1;
}
