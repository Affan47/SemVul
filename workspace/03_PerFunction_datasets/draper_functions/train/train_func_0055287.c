NSSCKFWC_DigestInit
(
  NSSCKFWInstance *fwInstance,
  CK_SESSION_HANDLE hSession,
  CK_MECHANISM_PTR pMechanism
)
{
  CK_RV error = CKR_OK;
  NSSCKFWSession *fwSession;
  NSSCKFWSlot  *fwSlot;
  NSSCKFWToken  *fwToken;
  NSSCKFWMechanism *fwMechanism;

  if (!fwInstance) {
    error = CKR_CRYPTOKI_NOT_INITIALIZED;
    goto loser;
  }

  fwSession = nssCKFWInstance_ResolveSessionHandle(fwInstance, hSession);
  if (!fwSession) {
    error = CKR_SESSION_HANDLE_INVALID;
    goto loser;
  }

  fwSlot = nssCKFWSession_GetFWSlot(fwSession);
  if (!fwSlot) {
    error = CKR_GENERAL_ERROR;
    goto loser;
  }

  if( CK_TRUE != nssCKFWSlot_GetTokenPresent(fwSlot) ) {
    error = CKR_TOKEN_NOT_PRESENT;
    goto loser;
  }

  fwToken = nssCKFWSlot_GetToken(fwSlot, &error);
  if (!fwToken) {
    goto loser;
  }

  fwMechanism = nssCKFWToken_GetMechanism(fwToken, pMechanism->mechanism, &error);
  if (!fwMechanism) {
    goto loser;
  }

  error = nssCKFWMechanism_DigestInit(fwMechanism, pMechanism, fwSession);

  nssCKFWMechanism_Destroy(fwMechanism);

  if (CKR_OK == error) {
    return CKR_OK;
  }

loser:

  switch( error ) {
  case CKR_ARGUMENTS_BAD:
  case CKR_CRYPTOKI_NOT_INITIALIZED:
  case CKR_DEVICE_ERROR:
  case CKR_DEVICE_MEMORY:
  case CKR_DEVICE_REMOVED:
  case CKR_FUNCTION_CANCELED:
  case CKR_FUNCTION_FAILED:
  case CKR_GENERAL_ERROR:
  case CKR_HOST_MEMORY:
  case CKR_MECHANISM_INVALID:
  case CKR_MECHANISM_PARAM_INVALID:
  case CKR_OPERATION_ACTIVE:
  case CKR_PIN_EXPIRED:
  case CKR_SESSION_CLOSED:
  case CKR_SESSION_HANDLE_INVALID:
  case CKR_USER_NOT_LOGGED_IN:
    break;
  default:
  case CKR_OK:
    error = CKR_GENERAL_ERROR;
    break;
  }
  return error;
}
