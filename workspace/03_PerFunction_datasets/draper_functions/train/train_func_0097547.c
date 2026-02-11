nssCKFWSession_GetRandom
(
  NSSCKFWSession *fwSession,
  NSSItem *buffer
)
{
  CK_RV error = CKR_OK;

#ifdef NSSDEBUG
  error = nssCKFWSession_verifyPointer(fwSession);
  if( CKR_OK != error ) {
    return error;
  }

  if (!buffer) {
    return CKR_ARGUMENTS_BAD;
  }

  if (!buffer->data) {
    return CKR_ARGUMENTS_BAD;
  }

  if (!fwSession->mdSession) {
    return CKR_GENERAL_ERROR;
  }
#endif

  if (!fwSession->mdSession->GetRandom) {
    if( CK_TRUE == nssCKFWToken_GetHasRNG(fwSession->fwToken) ) {
      return CKR_GENERAL_ERROR;
    } else {
      return CKR_RANDOM_NO_RNG;
    }
  }

  if( 0 == buffer->size ) {
    return CKR_OK;
  }

  error = fwSession->mdSession->GetRandom(fwSession->mdSession, fwSession,
    fwSession->mdToken, fwSession->fwToken, fwSession->mdInstance,
    fwSession->fwInstance, buffer);

  return error;
}
