NSS_CMSDigestedData_Decode_AfterData(NSSCMSDigestedData *digd)
{
    SECStatus rv = SECSuccess;

    if (digd->contentInfo.privateInfo && digd->contentInfo.privateInfo->digcx) {
	rv = NSS_CMSDigestContext_FinishSingle(digd->contentInfo.privateInfo->digcx,
				               digd->cmsg->poolp,
					       &(digd->cdigest));

	digd->contentInfo.privateInfo->digcx = NULL;
    }

    return rv;
}
