nssCKFWToken_Create
(
  NSSCKFWSlot *fwSlot,
  NSSCKMDToken *mdToken,
  CK_RV *pError
)
{
  NSSArena *arena = (NSSArena *)NULL;
  NSSCKFWToken *fwToken = (NSSCKFWToken *)NULL;
  CK_BBOOL called_setup = CK_FALSE;


  arena = NSSArena_Create();
  if (!arena) {
    *pError = CKR_HOST_MEMORY;
    goto loser;
  }

  fwToken = nss_ZNEW(arena, NSSCKFWToken);
  if (!fwToken) {
    *pError = CKR_HOST_MEMORY;
    goto loser;
  }

  fwToken->arena = arena;
  fwToken->mdToken = mdToken;
  fwToken->fwSlot = fwSlot;
  fwToken->fwInstance = nssCKFWSlot_GetFWInstance(fwSlot);
  fwToken->mdInstance = nssCKFWSlot_GetMDInstance(fwSlot);
  fwToken->state = CKS_RO_PUBLIC_SESSION;
  fwToken->sessionCount = 0;
  fwToken->rwSessionCount = 0;

  fwToken->mutex = nssCKFWInstance_CreateMutex(fwToken->fwInstance, arena, pError);
  if (!fwToken->mutex) {
    if( CKR_OK == *pError ) {
      *pError = CKR_GENERAL_ERROR;
    }
    goto loser;
  }

  fwToken->sessions = nssCKFWHash_Create(fwToken->fwInstance, arena, pError);
  if (!fwToken->sessions) {
    if( CKR_OK == *pError ) {
      *pError = CKR_GENERAL_ERROR;
    }
    goto loser;
  }

  if( CK_TRUE != nssCKFWInstance_GetModuleHandlesSessionObjects(
                   fwToken->fwInstance) ) {
    fwToken->sessionObjectHash = nssCKFWHash_Create(fwToken->fwInstance,
                                   arena, pError);
    if (!fwToken->sessionObjectHash) {
      if( CKR_OK == *pError ) {
        *pError = CKR_GENERAL_ERROR;
      }
      goto loser;
    }
  }

  fwToken->mdObjectHash = nssCKFWHash_Create(fwToken->fwInstance,
                            arena, pError);
  if (!fwToken->mdObjectHash) {
    if( CKR_OK == *pError ) {
      *pError = CKR_GENERAL_ERROR;
    }
    goto loser;
  }

  fwToken->mdMechanismHash = nssCKFWHash_Create(fwToken->fwInstance,
                            arena, pError);
  if (!fwToken->mdMechanismHash) {
    if( CKR_OK == *pError ) {
      *pError = CKR_GENERAL_ERROR;
    }
    goto loser;
  }


  if (mdToken->Setup) {
    *pError = mdToken->Setup(mdToken, fwToken, fwToken->mdInstance, fwToken->fwInstance);
    if( CKR_OK != *pError ) {
      goto loser;
    }
  }

  called_setup = CK_TRUE;

#ifdef DEBUG
  *pError = token_add_pointer(fwToken);
  if( CKR_OK != *pError ) {
    goto loser;
  }
#endif

  *pError = CKR_OK;
  return fwToken;

 loser:

  if( CK_TRUE == called_setup ) {
    if (mdToken->Invalidate) {
      mdToken->Invalidate(mdToken, fwToken, fwToken->mdInstance, fwToken->fwInstance);
    }
  }

  if (arena) {
    (void)NSSArena_Destroy(arena);
  }

  return (NSSCKFWToken *)NULL;
}
