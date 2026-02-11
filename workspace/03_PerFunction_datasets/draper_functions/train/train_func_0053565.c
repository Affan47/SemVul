nssutil_argDecodeSingleSlotInfo(char *name, char *params,
                               struct NSSUTILPreSlotInfoStr *slotInfo)
{
    char *askpw;

    slotInfo->slotID=NSSUTIL_ArgDecodeNumber(name);
    slotInfo->defaultFlags=NSSUTIL_ArgParseSlotFlags("slotFlags",params);
    slotInfo->timeout=NSSUTIL_ArgReadLong("timeout",params, 0, NULL);

    askpw = NSSUTIL_ArgGetParamValue("askpw",params);
    slotInfo->askpw = 0;

    if (askpw) {
	if (PORT_Strcasecmp(askpw,"every") == 0) {
    	    slotInfo->askpw = -1;
	} else if (PORT_Strcasecmp(askpw,"timeout") == 0) {
    	    slotInfo->askpw = 1;
	}
	PORT_Free(askpw);
	slotInfo->defaultFlags |= PK11_OWN_PW_DEFAULTS;
    }
    slotInfo->hasRootCerts = NSSUTIL_ArgHasFlag("rootFlags", "hasRootCerts",
                                               params);
    slotInfo->hasRootTrust = NSSUTIL_ArgHasFlag("rootFlags", "hasRootTrust",
                                               params);
}
