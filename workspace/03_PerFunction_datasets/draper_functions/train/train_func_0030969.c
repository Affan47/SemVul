nss_cmssignerinfo_create(NSSCMSMessage *cmsg, NSSCMSSignerIDSelector type,
	CERTCertificate *cert, SECItem *subjKeyID, SECKEYPublicKey *pubKey,
	SECKEYPrivateKey *signingKey, SECOidTag digestalgtag)
{
    void *mark;
    NSSCMSSignerInfo *signerinfo;
    int version;
    PLArenaPool *poolp;

    poolp = cmsg->poolp;

    mark = PORT_ArenaMark(poolp);

    signerinfo = (NSSCMSSignerInfo *)PORT_ArenaZAlloc(poolp, sizeof(NSSCMSSignerInfo));
    if (signerinfo == NULL) {
	PORT_ArenaRelease(poolp, mark);
	return NULL;
    }


    signerinfo->cmsg = cmsg;

    switch(type) {
    case NSSCMSSignerID_IssuerSN:
        signerinfo->signerIdentifier.identifierType = NSSCMSSignerID_IssuerSN;
        if ((signerinfo->cert = CERT_DupCertificate(cert)) == NULL)
	    goto loser;
        if ((signerinfo->signerIdentifier.id.issuerAndSN = CERT_GetCertIssuerAndSN(poolp, cert)) == NULL)
	    goto loser;
        break;
    case NSSCMSSignerID_SubjectKeyID:
        signerinfo->signerIdentifier.identifierType = NSSCMSSignerID_SubjectKeyID;
        PORT_Assert(subjKeyID);
        if (!subjKeyID)
            goto loser;

        signerinfo->signerIdentifier.id.subjectKeyID = PORT_ArenaNew(poolp, SECItem);
        SECITEM_CopyItem(poolp, signerinfo->signerIdentifier.id.subjectKeyID,
                         subjKeyID);
        signerinfo->signingKey = SECKEY_CopyPrivateKey(signingKey);
        if (!signerinfo->signingKey)
            goto loser;
        signerinfo->pubKey = SECKEY_CopyPublicKey(pubKey);
        if (!signerinfo->pubKey)
            goto loser;
        break;
    default:
        goto loser;
    }


    version = NSS_CMS_SIGNER_INFO_VERSION_ISSUERSN;

    if (signerinfo->signerIdentifier.identifierType == NSSCMSSignerID_SubjectKeyID)
	version = NSS_CMS_SIGNER_INFO_VERSION_SUBJKEY;
    (void)SEC_ASN1EncodeInteger(poolp, &(signerinfo->version), (long)version);

    if (SECOID_SetAlgorithmID(poolp, &signerinfo->digestAlg, digestalgtag, NULL) != SECSuccess)
	goto loser;

    PORT_ArenaUnmark(poolp, mark);
    return signerinfo;

loser:
    PORT_ArenaRelease(poolp, mark);
    return NULL;
}
