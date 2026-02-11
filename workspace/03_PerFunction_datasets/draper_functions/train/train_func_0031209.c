NSS_CMSSignerInfo_AddSMIMECaps(NSSCMSSignerInfo *signerinfo)
{
    NSSCMSAttribute *attr;
    SECItem *smimecaps = NULL;
    void *mark;
    PLArenaPool *poolp;

    poolp = signerinfo->cmsg->poolp;

    mark = PORT_ArenaMark(poolp);

    smimecaps = SECITEM_AllocItem(poolp, NULL, 0);
    if (smimecaps == NULL)
	goto loser;


    if (NSS_SMIMEUtil_CreateSMIMECapabilities(poolp, smimecaps) != SECSuccess)
	goto loser;

    if ((attr = NSS_CMSAttribute_Create(poolp, SEC_OID_PKCS9_SMIME_CAPABILITIES, smimecaps, PR_TRUE)) == NULL)
	goto loser;

    if (NSS_CMSSignerInfo_AddAuthAttr(signerinfo, attr) != SECSuccess)
	goto loser;

    PORT_ArenaUnmark (poolp, mark);
    return SECSuccess;

loser:
    PORT_ArenaRelease (poolp, mark);
    return SECFailure;
}
