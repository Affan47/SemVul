cmmf_PKIStatusInfoSetStatus(CMMFPKIStatusInfo    *statusInfo,
			    PLArenaPool          *poolp,
			    CMMFPKIStatus         inStatus)
{
    SECItem *dummy;

    if (inStatus <cmmfGranted || inStatus >= cmmfNumPKIStatus) {
        return SECFailure;
    }

    dummy = SEC_ASN1EncodeInteger(poolp, &statusInfo->status, inStatus);
    PORT_Assert(dummy == &statusInfo->status);
    if (dummy != &statusInfo->status) {
        SECITEM_FreeItem(dummy, PR_TRUE);
	return SECFailure;
    }
    return SECSuccess;
}
