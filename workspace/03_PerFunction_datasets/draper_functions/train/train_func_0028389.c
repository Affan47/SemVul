sendFilmBoxPrint(DUL_ASSOCIATIONKEY ** association,
		 DUL_ASSOCIATESERVICEPARAMETERS * params,
		 char *SOPClass, char *classUID, PRN_BASICFILMBOX * filmBox,
		 unsigned short *status)
{
    CONDITION
	cond;
    MSG_N_ACTION_REQ
	request;
    MSG_N_ACTION_RESP
	response;
    void
       *ctx = NULL;


    request.messageID = SRV_MessageIDOut();
    request.dataSetType = DCM_CMDDATANULL;
    request.actionTypeID = PRN_K_FILMBOX_ACTION_PRINT;
    request.type = MSG_K_N_ACTION_REQ;
    request.actionInformation = NULL;
    strcpy(request.classUID, DICOM_SOPCLASSBASICFILMBOX);
    strcpy(request.instanceUID, filmBox->filmBoxSOPInstanceUID);


    cond = SRV_NActionRequest(association, params, SOPClass,
			      &request, &response, filmBoxPrintCallback,
			      filmBox, ".");
    if (cond != SRV_NORMAL) {
	printf("In sendFilmBoxPrint : SRV_NActionRequest failed\n");
	return cond;
    }
    *status = response.status;
    return SRV_NORMAL;
}
