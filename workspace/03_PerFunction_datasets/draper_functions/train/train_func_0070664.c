crmf_modify_control_array (CRMFCertRequest *inCertReq, int count)
{
    if (count > 0) {
        void *dummy = PORT_Realloc(inCertReq->controls,
				   sizeof(CRMFControl*)*(count+2));
	if (dummy == NULL) {
	    return SECFailure;
	}
	inCertReq->controls = dummy;
    } else {
        inCertReq->controls = PORT_ZNewArray(CRMFControl*, 2);
    }
    return (inCertReq->controls == NULL) ? SECFailure : SECSuccess ;
}
