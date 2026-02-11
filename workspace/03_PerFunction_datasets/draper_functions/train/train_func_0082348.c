nssCKFWSession_Create
(
  NSSCKFWToken *fwToken,
  CK_BBOOL rw,
  CK_VOID_PTR pApplication,
  CK_NOTIFY Notify,
  CK_RV *pError
)
{
  NSSArena *arena = (NSSArena *)NULL;
  NSSCKFWSession *fwSession;
  NSSCKFWSlot *fwSlot;

#ifdef NSSDEBUG
  if (!pError) {
    return (NSSCKFWSession *)NULL;
  }

  *pError = nssCKFWToken_verifyPointer(fwToken);
  if( CKR_OK != *pError ) {
    return (NSSCKFWSession *)NULL;
  }
#endif

  arena = NSSArena_Create();
  if (!arena) {
    *pError = CKR_HOST_MEMORY;
    return (NSSCKFWSession *)NULL;
  }

  fwSession = nss_ZNEW(arena, NSSCKFWSession);
  if (!fwSession) {
    *pError = CKR_HOST_MEMORY;
    goto loser;
  }

  fwSession->arena = arena;
  fwSession->mdSession = (NSSCKMDSession *)NULL;
  fwSession->fwToken = fwToken;
  fwSession->mdToken = nssCKFWToken_GetMDToken(fwToken);

  fwSlot = nssCKFWToken_GetFWSlot(fwToken);
  fwSession->fwInstance = nssCKFWSlot_GetFWInstance(fwSlot);
  fwSession->mdInstance = nssCKFWSlot_GetMDInstance(fwSlot);

  fwSession->rw = rw;
  fwSession->pApplication = pApplication;
  fwSession->Notify = Notify;

  fwSession->fwFindObjects = (NSSCKFWFindObjects *)NULL;

  fwSession->sessionObjectHash = nssCKFWHash_Create(fwSession->fwInstance, arena, pError);
  if (!fwSession->sessionObjectHash) {
    if( CKR_OK == *pError ) {
      *pError = CKR_GENERAL_ERROR;
    }
    goto loser;
  }

#ifdef DEBUG
  *pError = session_add_pointer(fwSession);
  if( CKR_OK != *pError ) {
    goto loser;
  }
#endif

  return fwSession;

 loser:
  if (arena) {
    if (fwSession &&   fwSession->sessionObjectHash) {
      (void)nssCKFWHash_Destroy(fwSession->sessionObjectHash);
    }
    NSSArena_Destroy(arena);
  }

  return (NSSCKFWSession *)NULL;
}
