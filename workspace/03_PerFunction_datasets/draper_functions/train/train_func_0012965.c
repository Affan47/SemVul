nss_cmsrecipientinfo_usessubjectkeyid(NSSCMSRecipientInfo *ri)
{
    if (ri->recipientInfoType == NSSCMSRecipientInfoID_KeyTrans) {
	NSSCMSRecipientIdentifier *rid;
	rid = &ri->ri.keyTransRecipientInfo.recipientIdentifier;
	if (rid->identifierType == NSSCMSRecipientID_SubjectKeyID) {
	    return PR_TRUE;
	}
    }
    return PR_FALSE;
}
