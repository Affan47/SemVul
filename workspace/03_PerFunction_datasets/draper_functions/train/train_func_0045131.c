NSS_CMSEncryptedData_Create(NSSCMSMessage *cmsg, SECOidTag algorithm,
			    int keysize)
{
    void *mark;
    NSSCMSEncryptedData *encd;
    PLArenaPool *poolp;
    SECAlgorithmID *pbe_algid;
    SECStatus rv;

    poolp = cmsg->poolp;

    mark = PORT_ArenaMark(poolp);

    encd = PORT_ArenaZNew(poolp, NSSCMSEncryptedData);
    if (encd == NULL)
	goto loser;

    encd->cmsg = cmsg;


    if (!SEC_PKCS5IsAlgorithmPBEAlgTag(algorithm)) {
	rv = NSS_CMSContentInfo_SetContentEncAlg(poolp, &(encd->contentInfo),
						 algorithm, NULL, keysize);
    } else {


	pbe_algid = PK11_CreatePBEAlgorithmID(algorithm, 1, NULL);
	if (pbe_algid == NULL) {
	    rv = SECFailure;
	} else {
	    rv = NSS_CMSContentInfo_SetContentEncAlgID(poolp,
				&(encd->contentInfo), pbe_algid, keysize);
	    SECOID_DestroyAlgorithmID (pbe_algid, PR_TRUE);
	}
    }
    if (rv != SECSuccess)
	goto loser;

    PORT_ArenaUnmark(poolp, mark);
    return encd;

loser:
    PORT_ArenaRelease(poolp, mark);
    return NULL;
}
