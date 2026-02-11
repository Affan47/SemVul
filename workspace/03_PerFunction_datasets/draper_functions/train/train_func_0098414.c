CERT_GetConstrainedCertificateNames(const CERTCertificate *cert,
                                    PLArenaPool *arena,
                                    PRBool includeSubjectCommonName)
{
    CERTGeneralName  *DN;
    CERTGeneralName  *SAN;
    PRUint32         numDNSNames = 0;
    SECStatus        rv;

    if (!arena) {
    	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return NULL;
    }

    DN = CERT_NewGeneralName(arena, certDirectoryName);
    if (DN == NULL) {
	goto loser;
    }
    rv = CERT_CopyName(arena, &DN->name.directoryName, &cert->subject);
    if (rv != SECSuccess) {
	goto loser;
    }
    rv = SECITEM_CopyItem(arena, &DN->derDirectoryName, &cert->derSubject);
    if (rv != SECSuccess) {
	goto loser;
    }


    rv = cert_ExtractDNEmailAddrs(DN, arena);
    if (rv != SECSuccess)
        goto loser;


    SAN = cert_GetSubjectAltNameList(cert, arena);
    if (SAN) {
	numDNSNames = cert_CountDNSPatterns(SAN);
	DN = cert_CombineNamesLists(DN, SAN);
    }
    if (!numDNSNames && includeSubjectCommonName) {
	char *cn = CERT_GetCommonName(&cert->subject);
	if (cn) {
	    CERTGeneralName *CN = CERT_NewGeneralName(arena, certDNSName);
	    if (CN) {
		SECItem cnItem = {siBuffer, NULL, 0};
		cnItem.data = (unsigned char *)cn;
		cnItem.len  = strlen(cn);
		rv = SECITEM_CopyItem(arena, &CN->name.other, &cnItem);
		if (rv == SECSuccess) {
		    DN = cert_CombineNamesLists(DN, CN);
	        }
	    }
	    PORT_Free(cn);
	}
    }
    if (rv == SECSuccess) {

	return DN;
    }
loser:

    return NULL;
}
