createNEventDataSet(char *transactionUID, char *retrieveAETitle,
		    LST_HEAD * successes, LST_HEAD * failures,
		    DCM_OBJECT ** dataSet)
{
    CONDITION cond;

    DCM_ELEMENT *commitRefSOPSeq;
    DCM_ELEMENT *failedSOPSeq;

    cond = DCM_CreateObject(dataSet, 0);
    if (cond != DCM_NORMAL)
	return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
				  "Failed to allocate a new DCM object",
				  "createNEventDataSet");

    if (LST_Count(&successes) != 0) {
	cond = SQ_BuildSequence(&successes, SQ_K_REFERENCEDSOPSEQUENCE,
				&commitRefSOPSeq);
	if (cond != SQ_NORMAL)
	    return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
				  "Failed to build referenced SOP sequence",
				      "createNEventDataSet");

	cond = DCM_AddElement(dataSet, commitRefSOPSeq);
	if (cond != DCM_NORMAL)
	    return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
		      "Failed to add referenced SOP sequence to DCM object",
				      "createNEventDataSet");
    }
    if (LST_Count(&failures) != 0) {
	cond = SQ_BuildSequence(&failures, SQ_K_FAILEDSOPSEQUENCE,
				&failedSOPSeq);
	if (cond != SQ_NORMAL)
	    if (cond != SQ_NORMAL)
		return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
				      "Failed to build failed SOP sequence",
					  "createNEventDataSet");

	cond = DCM_AddElement(dataSet, failedSOPSeq);
	if (cond != DCM_NORMAL)
	    return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
			  "Failed to add failed SOP sequence to DCM object",
				      "createNEventDataSet");
    } {
	DCM_ELEMENT e = {DCM_IDTRANSACTIONUID, DCM_UI, "", 1, 0, NULL};
	e.length = strlen(transactionUID);
	e.d.string = transactionUID;
	cond = DCM_AddElement(dataSet, &e);
	if (cond != DCM_NORMAL)
	    return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
			      "Failed to add transaction UID to DCM object",
				      "createNEventDataSet");

    }
    {
	DCM_ELEMENT e = {DCM_IDRETRIEVEAETITLE, DCM_AE, "", 1, 0, NULL};
	e.length = strlen(retrieveAETitle);
	e.d.string = retrieveAETitle;
	cond = DCM_AddElement(dataSet, &e);
	if (cond != DCM_NORMAL)
	    return COND_PushCondition(APP_FAILURE, APP_Message(APP_FAILURE),
			    "Failed to add retrieve AE title to DCM object",
				      "createNEventDataSet");

    }

    return APP_NORMAL;
}
