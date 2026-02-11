lrm_signoff (ll_lrm_t* lrm)
{

	if (NULL != ch_cmd) {
		if (IPC_ISWCONN(ch_cmd)) {
	 		ch_cmd->ops->destroy(ch_cmd);
	 	}
		ch_cmd = NULL;
	}
	if (NULL != ch_cbk) {
		if (IPC_ISWCONN(ch_cbk)) {
			ch_cbk->ops->destroy(ch_cbk);
		}
		ch_cbk = NULL;
	}
	is_signed_on = FALSE;

	return HA_OK;
}
