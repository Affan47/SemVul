reset_b3_res(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
			 PLCI *plci, APPL *appl, API_PARSE *parms)
{
	word ncci;

	dbug(1, dprintf("reset_b3_res"));

	ncci = (word)(Id >> 16);
	if (plci && ncci) {
		switch (plci->B3_prot)
		{
		case B3_ISO8208:
		case B3_X25_DCE:
			if (a->ncci_state[ncci] == INC_RES_PENDING)
			{
				a->ncci_state[ncci] = CONNECTED;
				nl_req_ncci(plci, N_RESET_ACK, (byte)ncci);
				return true;
			}
			break;
		}
	}
	return false;
}
