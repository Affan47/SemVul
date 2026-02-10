sec_PKCS12NewCertBag(PLArenaPool *arena, SECOidTag certType)
{
    sec_PKCS12CertBag *certBag = NULL;
    SECOidData *bagType = NULL;
    SECStatus rv;
    void *mark = NULL;

    if(!arena) {
	return NULL;
    }

    mark = PORT_ArenaMark(arena);
    certBag = (sec_PKCS12CertBag *)PORT_ArenaZAlloc(arena,
    						    sizeof(sec_PKCS12CertBag));
    if(!certBag) {
	PORT_ArenaRelease(arena, mark);
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	return NULL;
    }

    bagType = SECOID_FindOIDByTag(certType);
    if(!bagType) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	goto loser;
    }

    rv = SECITEM_CopyItem(arena, &certBag->bagID, &bagType->oid);
    if(rv != SECSuccess) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	goto loser;
    }

    PORT_ArenaUnmark(arena, mark);
    return certBag;

loser:
    PORT_ArenaRelease(arena, mark);
    return NULL;
}
