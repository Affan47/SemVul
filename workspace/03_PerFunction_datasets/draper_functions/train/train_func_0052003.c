SEC_PKCS7IsContentEmpty(SEC_PKCS7ContentInfo *cinfo, unsigned int minLen)
{
    SECItem *item = NULL;

    if(cinfo == NULL) {
	return PR_TRUE;
    }

    switch(SEC_PKCS7ContentType(cinfo))
    {
	case SEC_OID_PKCS7_DATA:
	    item = cinfo->content.data;
	    break;
	case SEC_OID_PKCS7_ENCRYPTED_DATA:
	    item = &cinfo->content.encryptedData->encContentInfo.encContent;
	    break;
	default:

	    return PR_FALSE;
    }

    if(!item) {
	return PR_TRUE;
    } else if(item->len <= minLen) {
	return PR_TRUE;
    }

    return PR_FALSE;
}
