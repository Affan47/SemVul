CMMF_CreatePOPODecKeyRespContentFromDER(const char *buf, long len)
{
    PLArenaPool               *poolp;
    CMMFPOPODecKeyRespContent *decKeyResp;
    SECStatus                  rv;

    poolp = PORT_NewArena(CRMF_DEFAULT_ARENA_SIZE);
    if (poolp == NULL) {
        return NULL;
    }
    decKeyResp = PORT_ArenaZNew(poolp, CMMFPOPODecKeyRespContent);
    if (decKeyResp == NULL) {
        goto loser;
    }
    decKeyResp->poolp = poolp;
    rv = SEC_ASN1Decode(poolp, decKeyResp, CMMFPOPODecKeyRespContentTemplate,
			buf, len);
    if (rv != SECSuccess) {
        goto loser;
    }
    return decKeyResp;

 loser:
    if (poolp != NULL) {
        PORT_FreeArena(poolp, PR_FALSE);
    }
    return NULL;
}
