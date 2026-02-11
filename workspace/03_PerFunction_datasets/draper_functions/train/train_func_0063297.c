store_by_transfercallno(struct chan_iax2_pvt *pvt)
{
	if (!pvt->transfercallno) {
		ast_log(LOG_ERROR, "This should not be called without a transfer call number.\n");
		return;
	}

	ao2_link(iax_transfercallno_pvts, pvt);
}
