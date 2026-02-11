nssCKObject_IsAttributeTrue (
  CK_OBJECT_HANDLE object,
  CK_ATTRIBUTE_TYPE attribute,
  nssSession *session,
  NSSSlot *slot,
  PRStatus *rvStatus
)
{
    CK_BBOOL bool;
    CK_ATTRIBUTE_PTR attr;
    CK_ATTRIBUTE atemplate = { 0, NULL, 0 };
    CK_RV ckrv;
    void *epv = nssSlot_GetCryptokiEPV(slot);
    attr = &atemplate;
    NSS_CK_SET_ATTRIBUTE_VAR(attr, attribute, bool);
    nssSession_EnterMonitor(session);
    ckrv = CKAPI(epv)->C_GetAttributeValue(session->handle, object,
                                           &atemplate, 1);
    nssSession_ExitMonitor(session);
    if (ckrv != CKR_OK) {
	*rvStatus = PR_FAILURE;
	return PR_FALSE;
    }
    *rvStatus = PR_SUCCESS;
    return (PRBool)(bool == CK_TRUE);
}
