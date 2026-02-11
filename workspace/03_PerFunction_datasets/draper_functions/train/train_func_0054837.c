SECU_PrintCrl (FILE *out, SECItem *der, char *m, int level)
{
    PLArenaPool *arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    CERTCrl *c = NULL;
    int rv = SEC_ERROR_NO_MEMORY;

    if (!arena)
    	return rv;
    do {

	c = PORT_ArenaZNew(arena, CERTCrl);
	if (!c)
	    break;

	rv = SEC_QuickDERDecodeItem(arena, c, SEC_ASN1_GET(CERT_CrlTemplate), der);
	if (rv != SECSuccess)
	    break;
	SECU_PrintCRLInfo (out, c, m, level);
    } while (0);
    PORT_FreeArena (arena, PR_FALSE);
    return rv;
}
