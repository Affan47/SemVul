NSS_CMSDecoder_Finish(NSSCMSDecoderContext *p7dcx)
{
    NSSCMSMessage *cmsg;

    cmsg = p7dcx->cmsg;

    if (p7dcx->dcx == NULL ||
        SEC_ASN1DecoderFinish(p7dcx->dcx) != SECSuccess ||
	nss_cms_after_end(p7dcx) != SECSuccess)
    {
	NSS_CMSMessage_Destroy(cmsg);
	cmsg = NULL;
    }

    PORT_Free(p7dcx);
    return cmsg;
}
