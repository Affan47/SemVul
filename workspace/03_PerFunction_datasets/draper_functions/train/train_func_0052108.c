NSS_CMSRecipientInfo_GetEncryptedKey(NSSCMSRecipientInfo *ri, int subIndex)
{
    SECItem *enckey = NULL;

    switch (ri->recipientInfoType) {
    case NSSCMSRecipientInfoID_KeyTrans:

	enckey = &(ri->ri.keyTransRecipientInfo.encKey);
	break;
    case NSSCMSRecipientInfoID_KEK:

	enckey = &(ri->ri.kekRecipientInfo.encKey);
	break;
    case NSSCMSRecipientInfoID_KeyAgree:
	enckey = &(ri->ri.keyAgreeRecipientInfo.recipientEncryptedKeys[subIndex]->encKey);
	break;
    }
    return enckey;
}
