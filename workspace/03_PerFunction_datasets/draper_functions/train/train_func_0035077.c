setImageBox(DUL_ASSOCIATIONKEY ** association,
	    DUL_ASSOCIATESERVICEPARAMETERS * params,
	    char *SOPClass,
	    PRN_BASICIMAGEBOX * imageBox,
	    unsigned short *status)
{
    MSG_N_SET_REQ
	request;
    MSG_N_SET_RESP
	response;
    DCM_ELEMENT
	* e;
    DCM_SEQUENCE_ITEM
	* item;
    CONDITION
	cond;
    int
        uc;
    void
       *ctx = NULL;
    unsigned long
        length;


    request.messageID = SRV_MessageIDOut();
    request.type = MSG_K_N_SET_REQ;
    strcpy(request.classUID, DICOM_SOPCLASSBASICGREYSCALEIMAGEBOX);
    strcpy(request.instanceUID, imageBox->imageBoxSOPInstanceUID);
    request.dataSetType = DCM_CMDDATAOTHER;

    cond = PRN_BuildObject(imageBox, &request.dataSet);
    if (cond != PRN_NORMAL) {
	printf("In setImageBox : PRN_CreateObject failed\n");
	return cond;
    }
    if (!silent) {
	printf("Dumping Request data set\n");
	(void) DCM_DumpElements(&request.dataSet, 0);
    }


    cond = SRV_NSetRequest(association, params, SOPClass,
		   &request, &response, setImageBoxCallback, imageBox, ".");
    if (cond != SRV_NORMAL) {
	printf("In setImageBox : SRV_NSetRequest failed\n");
	return cond;
    }
    cond = DCM_CloseObject(&request.dataSet);
    if (cond != DCM_NORMAL) {
	printf("In setImageBox : DCM_CloseObject failed\n");
	return cond;
    }
    *status = response.status;
    return SRV_NORMAL;
}
