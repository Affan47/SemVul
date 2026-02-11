CERT_DecodeOCSPRequest(const SECItem *src)
{
    PLArenaPool *arena = NULL;
    SECStatus rv = SECFailure;
    CERTOCSPRequest *dest = NULL;
    int i;
    SECItem newSrc;

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL) {
	goto loser;
    }
    dest = (CERTOCSPRequest *) PORT_ArenaZAlloc(arena,
						sizeof(CERTOCSPRequest));
    if (dest == NULL) {
	goto loser;
    }
    dest->arena = arena;


    rv = SECITEM_CopyItem(arena, &newSrc, src);
    if ( rv != SECSuccess ) {
	goto loser;
    }

    rv = SEC_QuickDERDecodeItem(arena, dest, ocsp_OCSPRequestTemplate, &newSrc);
    if (rv != SECSuccess) {
	if (PORT_GetError() == SEC_ERROR_BAD_DER)
	    PORT_SetError(SEC_ERROR_OCSP_MALFORMED_REQUEST);
	goto loser;
    }


    for (i = 0; dest->tbsRequest->requestList[i] != NULL; i++) {
	dest->tbsRequest->requestList[i]->arena = arena;
    }

    return dest;

loser:
    if (arena != NULL) {
	PORT_FreeArena(arena, PR_FALSE);
    }
    return NULL;
}
