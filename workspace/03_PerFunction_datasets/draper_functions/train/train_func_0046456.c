NSSCKFWC_SetOperationState
(
  NSSCKFWInstance *fwInstance,
  CK_SESSION_HANDLE hSession,
  CK_BYTE_PTR pOperationState,
  CK_ULONG ulOperationStateLen,
  CK_OBJECT_HANDLE hEncryptionKey,
  CK_OBJECT_HANDLE hAuthenticationKey
)
{
  CK_RV error = CKR_OK;
  NSSCKFWSession *fwSession;
  NSSCKFWObject *eKey;
  NSSCKFWObject *aKey;
  NSSItem state;

  if (!fwInstance) {
    error = CKR_CRYPTOKI_NOT_INITIALIZED;
    goto loser;
  }

  if( (CK_BYTE_PTR)CK_NULL_PTR == pOperationState ) {
    error = CKR_ARGUMENTS_BAD;
    goto loser;
  }


  fwSession = nssCKFWInstance_ResolveSessionHandle(fwInstance, hSession);
  if (!fwSession) {
    error = CKR_SESSION_HANDLE_INVALID;
    goto loser;
  }

  if( (CK_OBJECT_HANDLE)0 == hEncryptionKey ) {
    eKey = (NSSCKFWObject *)NULL;
  } else {
    eKey = nssCKFWInstance_ResolveObjectHandle(fwInstance, hEncryptionKey);
    if (!eKey) {
      error = CKR_KEY_HANDLE_INVALID;
      goto loser;
    }
  }

  if( (CK_OBJECT_HANDLE)0 == hAuthenticationKey ) {
    aKey = (NSSCKFWObject *)NULL;
  } else {
    aKey = nssCKFWInstance_ResolveObjectHandle(fwInstance, hAuthenticationKey);
    if (!aKey) {
      error = CKR_KEY_HANDLE_INVALID;
      goto loser;
    }
  }

  state.data = pOperationState;
  state.size = ulOperationStateLen;

  error = nssCKFWSession_SetOperationState(fwSession, &state, eKey, aKey);
  if( CKR_OK != error ) {
    goto loser;
  }

  return CKR_OK;

 loser:
  switch( error ) {
  case CKR_SESSION_CLOSED:

    break;
  case CKR_DEVICE_REMOVED:

    break;
  case CKR_CRYPTOKI_NOT_INITIALIZED:
  case CKR_DEVICE_ERROR:
  case CKR_DEVICE_MEMORY:
  case CKR_FUNCTION_FAILED:
  case CKR_GENERAL_ERROR:
  case CKR_HOST_MEMORY:
  case CKR_KEY_CHANGED:
  case CKR_KEY_NEEDED:
  case CKR_KEY_NOT_NEEDED:
  case CKR_SAVED_STATE_INVALID:
  case CKR_SESSION_HANDLE_INVALID:
    break;
  default:
  case CKR_OK:
    error = CKR_GENERAL_ERROR;
    break;
  }

  return error;
}
