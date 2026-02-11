CMMF_KeyRecRepContentSetPKIStatusInfoStatus(CMMFKeyRecRepContent *inKeyRecRep,
					    CMMFPKIStatus         inPKIStatus)
{
    PORT_Assert(inKeyRecRep != NULL && inPKIStatus >= cmmfGranted &&
		inPKIStatus < cmmfNumPKIStatus);
    if (inKeyRecRep == NULL) {
        return SECFailure;
    }

    return cmmf_PKIStatusInfoSetStatus(&inKeyRecRep->status,
				       inKeyRecRep->poolp,
				       inPKIStatus);
}
