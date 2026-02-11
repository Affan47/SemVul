NSS_CMSMessage_IsEncrypted(NSSCMSMessage *cmsg)
{
    NSSCMSContentInfo *cinfo;


    for (cinfo = &(cmsg->contentInfo); cinfo != NULL; cinfo = NSS_CMSContentInfo_GetChildContentInfo(cinfo))
    {
	switch (NSS_CMSContentInfo_GetContentTypeTag(cinfo)) {
	case SEC_OID_PKCS7_ENVELOPED_DATA:
	case SEC_OID_PKCS7_ENCRYPTED_DATA:
	    return PR_TRUE;
	default:

	    break;
	}
    }
    return PR_FALSE;
}
