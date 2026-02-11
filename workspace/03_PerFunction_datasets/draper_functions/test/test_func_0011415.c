CERT_CopyGeneralName(PLArenaPool      *arena,
		     CERTGeneralName  *dest,
		     CERTGeneralName  *src)
{
    SECStatus rv;
    CERTGeneralName *destHead = dest;
    CERTGeneralName *srcHead = src;

    PORT_Assert(dest != NULL);
    if (!dest) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return SECFailure;
    }

    do {
	rv = cert_CopyOneGeneralName(arena, dest, src);
	if (rv != SECSuccess)
	    goto loser;
	src = CERT_GetNextGeneralName(src);

	if (src != srcHead) {
	    if (dest->l.next == &destHead->l) {
		CERTGeneralName *temp;
		temp = CERT_NewGeneralName(arena, (CERTGeneralNameType)0);
		if (!temp)
		    goto loser;
		temp->l.next = &destHead->l;
		temp->l.prev = &dest->l;
		destHead->l.prev = &temp->l;
		dest->l.next = &temp->l;
		dest = temp;
	    } else {
		dest = CERT_GetNextGeneralName(dest);
	    }
	}
    } while (src != srcHead && rv == SECSuccess);

    return rv;
loser:

    return SECFailure;
}
