channel_request_xon(PLCI *plci, byte ch) {
	DIVA_CAPI_ADAPTER *a = plci->adapter;

	if (a->ch_flow_control[ch] & N_CH_XOFF) {
		a->ch_flow_control[ch] |= N_XON_REQ;
		a->ch_flow_control[ch] &= ~N_CH_XOFF;
		a->ch_flow_control[ch] &= ~N_XON_CONNECT_IND;
	}
}
