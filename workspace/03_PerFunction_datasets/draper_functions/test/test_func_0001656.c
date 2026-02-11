syb_st_STORE_attrib(SV *sth, imp_sth_t *imp_sth, SV *keysv, SV *valuesv) {
	dTHX;
	STRLEN kl;
	char *key = SvPV(keysv, kl);
	T_st_params *par;

	if (DBIc_DBISTATE(imp_sth)->debug >= 3) {
		PerlIO_printf(DBIc_LOGPIO(imp_sth), "    syb_st_STORE(): key = %s\n",
				key);
	}

	for (par = S_st_store_params; par->len > 0; par++)
		if (par->len == kl && strEQ(key, par->str))
			break;

	if (par->len <= 0)
		return FALSE;

	if (DBIc_DBISTATE(imp_sth)->debug >= 3) {
		PerlIO_printf(DBIc_LOGPIO(imp_sth),
				"    syb_st_STORE(): storing %d for key = %s\n",
				SvTRUE(valuesv), key);
	}
	switch (par - S_st_store_params) {
	case 0:
		if (SvTRUE(valuesv)) {
			imp_sth->doProcStatus = 1;
		} else {
			imp_sth->doProcStatus = 0;
		}
		return TRUE;
	case 1:
		if (SvTRUE(valuesv)) {
			imp_sth->noBindBlob = 1;
		} else {
			imp_sth->noBindBlob = 0;
		}
		return TRUE;
	}
	return FALSE;
}
