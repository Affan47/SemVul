nssCKFWSession_GetOperationStateLen
(
  NSSCKFWSession *fwSession,
  CK_RV *pError
)
{
  CK_ULONG mdAmt;
  CK_ULONG fwAmt;

#ifdef NSSDEBUG
  if (!pError) {
    return (CK_ULONG)0;
  }

  *pError = nssCKFWSession_verifyPointer(fwSession);
  if( CKR_OK != *pError ) {
    return (CK_ULONG)0;
  }

  if (!fwSession->mdSession) {
    *pError = CKR_GENERAL_ERROR;
    return (CK_ULONG)0;
  }
#endif

  if (!fwSession->mdSession->GetOperationStateLen) {
    *pError = CKR_STATE_UNSAVEABLE;
    return (CK_ULONG)0;
  }


  mdAmt = fwSession->mdSession->GetOperationStateLen(fwSession->mdSession,
    fwSession, fwSession->mdToken, fwSession->fwToken, fwSession->mdInstance,
    fwSession->fwInstance, pError);

  if( ((CK_ULONG)0 == mdAmt) && (CKR_OK != *pError) ) {
    return (CK_ULONG)0;
  }


  fwAmt = mdAmt + 2*sizeof(CK_ULONG);

  return fwAmt;
}
