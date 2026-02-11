__lv_ckp_vrfy_handler(lvinfo, txninfop, param)
	DB_LOG_VRFY_INFO *lvinfo;
	VRFY_TXN_INFO *txninfop;
	void *param;
{
	struct __ckp_verify_params *cvp;
	int ret;

	ret = 0;
	cvp = (struct __ckp_verify_params *)param;

	if (txninfop->status == TXN_STAT_ACTIVE && LOG_COMPARE(&(cvp->ckp_lsn),
	    &(txninfop->first_lsn)) >= 0) {
		__db_errx(cvp->env, DB_STR_A("2552",
		    "[%lu][%lu] ckp log's ckp_lsn [%lu][%lu] greater than "
		    "active txn %lx 's first lsn [%lu][%lu]",
		     "%lu %lu %lu %lu %lx %lu %lu"),
		    (u_long)cvp->lsn.file, (u_long)cvp->lsn.offset,
		    (u_long)cvp->ckp_lsn.file, (u_long)cvp->ckp_lsn.offset,
		    (u_long)txninfop->txnid,
		    (u_long)txninfop->first_lsn.file,
		    (u_long)txninfop->first_lsn.offset);
		lvinfo->flags |= DB_LOG_VERIFY_ERR;
		if (!F_ISSET(lvinfo, DB_LOG_VERIFY_CAF))

			ret = DB_LOG_VERIFY_BAD;
	}

	return (ret);
}
