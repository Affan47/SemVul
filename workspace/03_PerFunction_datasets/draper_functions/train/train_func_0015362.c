cert_PkixToNssCertsChain(
    PKIX_List *pkixCertChain,
    CERTCertList **pvalidChain,
    void *plContext)
{
    PLArenaPool     *arena = NULL;
    CERTCertificate *nssCert = NULL;
    CERTCertList    *validChain = NULL;
    PKIX_PL_Object  *certItem = NULL;
    PKIX_UInt32      length = 0;
    PKIX_UInt32      i = 0;

    PKIX_ENTER(CERTVFYPKIX, "cert_PkixToNssCertsChain");
    PKIX_NULLCHECK_ONE(pvalidChain);

    if (pkixCertChain == NULL) {
        goto cleanup;
    }
    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL) {
        PKIX_ERROR(PKIX_OUTOFMEMORY);
    }
    validChain = (CERTCertList*)PORT_ArenaZAlloc(arena, sizeof(CERTCertList));
    if (validChain == NULL) {
        PKIX_ERROR(PKIX_PORTARENAALLOCFAILED);
    }
    PR_INIT_CLIST(&validChain->list);
    validChain->arena = arena;
    arena = NULL;

    PKIX_CHECK(
        PKIX_List_GetLength(pkixCertChain, &length, plContext),
        PKIX_LISTGETLENGTHFAILED);

    for (i = 0; i < length; i++){
        CERTCertListNode *node = NULL;

        PKIX_CHECK(
            PKIX_List_GetItem(pkixCertChain, i, &certItem, plContext),
            PKIX_LISTGETITEMFAILED);

        PKIX_CHECK(
            PKIX_PL_Cert_GetCERTCertificate((PKIX_PL_Cert*)certItem, &nssCert,
                                    plContext),
            PKIX_CERTGETCERTCERTIFICATEFAILED);

        node =
            (CERTCertListNode *)PORT_ArenaZAlloc(validChain->arena,
                                                 sizeof(CERTCertListNode));
        if ( node == NULL ) {
            PKIX_ERROR(PKIX_PORTARENAALLOCFAILED);
        }

        PR_INSERT_BEFORE(&node->links, &validChain->list);

        node->cert = nssCert;
        nssCert = NULL;

        PKIX_DECREF(certItem);
    }

    *pvalidChain = validChain;

cleanup:
    if (PKIX_ERROR_RECEIVED){
        if (validChain) {
            CERT_DestroyCertList(validChain);
        } else if (arena) {
            PORT_FreeArena(arena, PR_FALSE);
        }
        if (nssCert) {
            CERT_DestroyCertificate(nssCert);
        }
    }
    PKIX_DECREF(certItem);

    PKIX_RETURN(CERTVFYPKIX);
}
