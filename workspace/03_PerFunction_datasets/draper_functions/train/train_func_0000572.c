alert_req(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
		      PLCI *plci, APPL *appl, API_PARSE *msg)
{
	word Info;
	byte ret;

	dbug(1, dprintf("alert_req"));

	Info = _WRONG_IDENTIFIER;
	ret = false;
	if (plci) {
		Info = _ALERT_IGNORED;
		if (plci->State != INC_CON_ALERT) {
			Info = _WRONG_STATE;
			if (plci->State == INC_CON_PENDING) {
				Info = 0;
				plci->State = INC_CON_ALERT;
				add_ai(plci, &msg[0]);
				sig_req(plci, CALL_ALERT, 0);
				ret = 1;
			}
		}
	}
	sendf(appl,
	      _ALERT_R | CONFIRM,
	      Id,
	      Number,
	      "w", Info);
	return ret;
}
