cert_DupOCSPCertID(const CERTOCSPCertID *src)
{
    CERTOCSPCertID *dest;
    PLArenaPool *arena = NULL;

    if (!src) {
        PORT_SetError(SEC_ERROR_INVALID_ARGS);
        return NULL;
    }

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (!arena)
        goto loser;

    dest = PORT_ArenaZNew(arena, CERTOCSPCertID);
    if (!dest)
        goto loser;

#define DUPHELP(element) \
    if (src->element.data && \
        SECITEM_CopyItem(arena, &dest->element, &src->element) \
        != SECSuccess) { \
        goto loser; \
    }

    DUPHELP(hashAlgorithm.algorithm)
    DUPHELP(hashAlgorithm.parameters)
    DUPHELP(issuerNameHash)
    DUPHELP(issuerKeyHash)
    DUPHELP(serialNumber)
    DUPHELP(issuerSHA1NameHash)
    DUPHELP(issuerMD5NameHash)
    DUPHELP(issuerMD2NameHash)
    DUPHELP(issuerSHA1KeyHash)
    DUPHELP(issuerMD5KeyHash)
    DUPHELP(issuerMD2KeyHash)

    dest->poolp = arena;
    return dest;

loser:
    if (arena)
        PORT_FreeArena(arena, PR_FALSE);
    PORT_SetError(PR_OUT_OF_MEMORY_ERROR);
    return NULL;
}
