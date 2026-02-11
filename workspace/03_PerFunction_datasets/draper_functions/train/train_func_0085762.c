CRMF_CertRequestIsControlPresent(CRMFCertRequest *inCertReq,
				 CRMFControlType  inControlType)
{
    SECOidTag controlTag;
    int       i;

    PORT_Assert(inCertReq != NULL);
    if (inCertReq == NULL || inCertReq->controls == NULL) {
        return PR_FALSE;
    }
    controlTag = crmf_controltype_to_tag(inControlType);
    for (i=0; inCertReq->controls[i] != NULL; i++) {
        if (inCertReq->controls[i]->tag == controlTag) {
	    return PR_TRUE;
	}
    }
    return PR_FALSE;
}
