channel_xmit_extended_xon(PLCI *plci) {
	DIVA_CAPI_ADAPTER *a;
	int max_ch = ARRAY_SIZE(a->ch_flow_control);
	int i, one_requested = 0;

	if ((!plci) || (!plci->Id) || ((a = plci->adapter) == NULL)) {
		return;
	}

	for (i = 0; i < max_ch; i++) {
		if ((a->ch_flow_control[i] & N_CH_XOFF) &&
		    (a->ch_flow_control[i] & N_XON_CONNECT_IND) &&
		    (plci->Id == a->ch_flow_plci[i])) {
			channel_request_xon(plci, (byte)i);
			one_requested = 1;
		}
	}

	if (one_requested) {
		channel_xmit_xon(plci);
	}
}
