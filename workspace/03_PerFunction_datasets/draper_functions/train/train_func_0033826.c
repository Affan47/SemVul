isp_handle_conn_event(struct cpssp *cpssp, enum sig_telephone_protocol event)
{
	switch(event) {
	case SIG_TELE_BUSY:

		cpssp->isp_state = STATE_OFFLINE;
		isp_reset(cpssp);
		return;
	default:
		faum_log(FAUM_LOG_DEBUG, "node-isp", __func__,
				"invalid protocol!\n");
	}
}
