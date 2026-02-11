checkCallingNode(char *node, DUL_ASSOCIATESERVICEPARAMETERS * params,
     CTNBOOLEAN forgive, DMAN_HANDLE ** handle, DUL_ABORTITEMS * abortItems)
{
    CONDITION
    cond,
    rtnCond = APP_NORMAL;

    cond = DMAN_VerifyApplication(handle, params->callingAPTitle,
				  params->callingPresentationAddress);
    if (cond != DMAN_NORMAL) {
	rtnCond = COND_PushCondition(APP_ILLEGALSERVICEPARAMETER,
				   APP_Message(APP_ILLEGALSERVICEPARAMETER),
				"Calling AE Title", params->callingAPTitle);
    }
    if (rtnCond != APP_NORMAL) {
	abortItems->result = DUL_REJECT_PERMANENT;
	abortItems->source = DUL_ULSU_REJECT;
	abortItems->reason = DUL_ULSU_REJ_UNREC_CALLED_TITLE;
    }
    return rtnCond;
}
