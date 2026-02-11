listen_req(dword Id, word Number, DIVA_CAPI_ADAPTER *a,
		       PLCI *plci, APPL *appl, API_PARSE *parms)
{
	word Info;
	byte i;

	dbug(1, dprintf("listen_req(Appl=0x%x)", appl->Id));

	Info = _WRONG_IDENTIFIER;
	if (a) {
		Info = 0;
		a->Info_Mask[appl->Id - 1] = GET_DWORD(parms[0].info);
		a->CIP_Mask[appl->Id - 1] = GET_DWORD(parms[1].info);
		dbug(1, dprintf("CIP_MASK=0x%lx", GET_DWORD(parms[1].info)));
		if (a->Info_Mask[appl->Id - 1] & 0x200) {
			a->Info_Mask[appl->Id - 1] |=  0x10;
		}


		if (Id&EXT_CONTROLLER && GET_DWORD(parms[1].info)) {
			if (a->profile.Global_Options & ON_BOARD_CODEC) {
				dummy_plci.State = IDLE;
				a->codec_listen[appl->Id - 1] = &dummy_plci;
				a->TelOAD[0] = (byte)(parms[3].length);
				for (i = 1; parms[3].length >= i && i < 22; i++) {
					a->TelOAD[i] = parms[3].info[i];
				}
				a->TelOAD[i] = 0;
				a->TelOSA[0] = (byte)(parms[4].length);
				for (i = 1; parms[4].length >= i && i < 22; i++) {
					a->TelOSA[i] = parms[4].info[i];
				}
				a->TelOSA[i] = 0;
			}
			else Info = 0x2002;
		}
		else{
			a->codec_listen[appl->Id - 1] = (PLCI *)0;
		}
	}
	sendf(appl,
	      _LISTEN_R | CONFIRM,
	      Id,
	      Number,
	      "w", Info);

	if (a) listen_check(a);
	return false;
}
