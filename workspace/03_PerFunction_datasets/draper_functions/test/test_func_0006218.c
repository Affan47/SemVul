CRMF_POPOPrivGetKeySubseqMess(CRMFPOPOPrivKey       *inKey,
			      CRMFSubseqMessOptions *destOpt)
{
    long      value;
    SECStatus rv;

    PORT_Assert(inKey != NULL);
    if (inKey == NULL ||
	inKey->messageChoice != crmfSubsequentMessage) {
        return SECFailure;
    }
    rv = crmf_extract_long_from_item(&inKey->message.subsequentMessage,&value);
    if (rv != SECSuccess) {
        return SECFailure;
    }
    switch (value) {
    case 0:
        *destOpt = crmfEncrCert;
	break;
    case 1:
        *destOpt = crmfChallengeResp;
	break;
    default:
        rv = SECFailure;
    }
    if (rv != SECSuccess) {
        return rv;
    }
    return SECSuccess;
}
