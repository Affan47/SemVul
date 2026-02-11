CERT_AddCertToListTailWithData(CERTCertList *certs,
				CERTCertificate *cert, void *appData)
{
    CERTCertListNode *node;

    node = (CERTCertListNode *)PORT_ArenaZAlloc(certs->arena,
						sizeof(CERTCertListNode));
    if ( node == NULL ) {
	goto loser;
    }

    PR_INSERT_BEFORE(&node->links, &certs->list);

    node->cert = cert;
    node->appData = appData;
    return(SECSuccess);

loser:
    return(SECFailure);
}
