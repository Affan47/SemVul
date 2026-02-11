nssCKFWSession_CallNotification
(
  NSSCKFWSession *fwSession,
  CK_NOTIFICATION event
)
{
  CK_RV error = CKR_OK;
  CK_SESSION_HANDLE handle;

#ifdef NSSDEBUG
  error = nssCKFWSession_verifyPointer(fwSession);
  if( CKR_OK != error ) {
    return error;
  }
#endif

  if( (CK_NOTIFY)NULL == fwSession->Notify ) {
    return CKR_OK;
  }

  handle = nssCKFWInstance_FindSessionHandle(fwSession->fwInstance, fwSession);
  if( (CK_SESSION_HANDLE)0 == handle ) {
    return CKR_GENERAL_ERROR;
  }

  error = fwSession->Notify(handle, event, fwSession->pApplication);

  return error;
}
