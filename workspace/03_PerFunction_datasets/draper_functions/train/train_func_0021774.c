nssCKFWSession_RegisterSessionObject
(
  NSSCKFWSession *fwSession,
  NSSCKFWObject *fwObject
)
{
  CK_RV rv = CKR_OK;

#ifdef NSSDEBUG
  if( CKR_OK != nssCKFWSession_verifyPointer(fwSession) ) {
    return CKR_GENERAL_ERROR;
  }
#endif

  if (fwSession->sessionObjectHash) {
    rv = nssCKFWHash_Add(fwSession->sessionObjectHash, fwObject, fwObject);
  }

  return rv;
}
