setRequest(DUL_ASSOCIATIONKEY ** association,
	   DUL_PRESENTATIONCONTEXT * ctx, MSG_N_SET_REQ ** request,
	   CTNBOOLEAN * sendBack)
{
    MSG_N_SET_RESP
	setResponse;
    CONDITION
	cond = SRV_NORMAL;


    memset((void *) &setResponse, 0, sizeof(MSG_N_SET_RESP));


    if (strcmp((*request)->classUID,
	       DICOM_SOPCLASSBASICGREYSCALEIMAGEBOX) == 0) {
	(void) COND_PopCondition(TRUE);
	cond = SRV_NSetResponse(association, ctx, request, &setResponse,
				nsetImageBoxCallback, sendBack, ".");
	if (cond != SRV_NORMAL) {
	    printf("In setRequest : SRV_NSetResponse failed\n");
	    return cond;
	}
	if (traceFlag) {
	    printf("AFTER setting attributes of Grayscale IMAGE BOX\n");
	    showHierarchy();
	}
	return cond;
    } else if (strcmp((*request)->classUID,
		      DICOM_SOPCLASSBASICCOLORIMAGEBOX) == 0) {
	(void) COND_PopCondition(TRUE);
	cond = SRV_NSetResponse(association, ctx, request, &setResponse,
				nsetImageBoxCallback, sendBack, ".");
	if (cond != SRV_NORMAL) {
	    printf("In setRequest : SRV_NSetResponse failed\n");
	    return cond;
	}
	if (traceFlag) {
	    printf("AFTER setting attributes of Color IMAGE BOX\n");
	    showHierarchy();
	}
	return cond;
    } else if (strcmp((*request)->classUID,
		      DICOM_SOPCLASSBASICFILMSESSION) == 0) {
	(void) COND_PopCondition(TRUE);
	cond = SRV_NSetResponse(association, ctx, request, &setResponse,
				nsetBFSCallback, sendBack, ".");
	if (cond != SRV_NORMAL) {
	    printf("In setRequest : SRV_NSetResponse failed\n");
	    return cond;
	}
	if (traceFlag) {
	    printf("AFTER setting attributes of BASIC FILM SESSION\n");
	    showHierarchy();
	}
	return cond;
#ifdef ASG
    } else if (strcmp((*request)->classUID,
		      DICOM_SOPCLASSBASICFILMBOX) == 0) {
	(void) COND_PopCondition(TRUE);
	cond = SRV_NSetResponse(association, ctx, request, &setResponse,
				nsetBFBCallback, sendBack, ".");
	if (cond != SRV_NORMAL) {
	    printf("In setRequest : SRV_NSetResponse failed\n");
	    return cond;
	}
	if (traceFlag) {
	    printf("AFTER setting attributes of BASIC FILM BOX\n");
	    showHierarchy();
	}
	return cond;
#endif
    } else {

	cond = SRV_NSetResponse(association, ctx, request, &setResponse,
				unsupportedCallback, sendBack, ".");
	if (cond != SRV_NORMAL) {
	    printf("In setRequest : SRV_NSetResponse failed\n");
	    return cond;
	}
	return cond;
    }
}
