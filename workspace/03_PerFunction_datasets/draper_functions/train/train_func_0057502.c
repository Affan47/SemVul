NSS_CMSRecipientInfo_GetVersion(NSSCMSRecipientInfo *ri)
{
    unsigned long version;
    SECItem *versionitem = NULL;

    switch (ri->recipientInfoType) {
    case NSSCMSRecipientInfoID_KeyTrans:

	versionitem = &(ri->ri.keyTransRecipientInfo.version);
	break;
    case NSSCMSRecipientInfoID_KEK:

	versionitem = &(ri->ri.kekRecipientInfo.version);
	break;
    case NSSCMSRecipientInfoID_KeyAgree:
	versionitem = &(ri->ri.keyAgreeRecipientInfo.version);
	break;
    }

    PORT_Assert(versionitem);
    if (versionitem == NULL)
	return 0;


    if (SEC_ASN1DecodeInteger(versionitem, &version) != SECSuccess)
	return 0;
    else
	return (int)version;
}
