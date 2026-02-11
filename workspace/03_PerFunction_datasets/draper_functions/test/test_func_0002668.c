PK11_NewSlotInfo(SECMODModule *mod)
{
    PK11SlotInfo *slot;

    slot = (PK11SlotInfo *)PORT_Alloc(sizeof(PK11SlotInfo));
    if (slot == NULL) return slot;

    slot->sessionLock = mod->isThreadSafe ?
	PZ_NewLock(nssILockSession) : mod->refLock;
    if (slot->sessionLock == NULL) {
	PORT_Free(slot);
	return NULL;
    }
    slot->freeListLock = PZ_NewLock(nssILockFreelist);
    if (slot->freeListLock == NULL) {
	if (mod->isThreadSafe) {
	    PZ_DestroyLock(slot->sessionLock);
	}
	PORT_Free(slot);
	return NULL;
    }
    slot->freeSymKeysWithSessionHead = NULL;
    slot->freeSymKeysHead = NULL;
    slot->keyCount = 0;
    slot->maxKeyCount = 0;
    slot->functionList = NULL;
    slot->needTest = PR_TRUE;
    slot->isPerm = PR_FALSE;
    slot->isHW = PR_FALSE;
    slot->isInternal = PR_FALSE;
    slot->isThreadSafe = PR_FALSE;
    slot->disabled = PR_FALSE;
    slot->series = 1;
    slot->wrapKey = 0;
    slot->wrapMechanism = CKM_INVALID_MECHANISM;
    slot->refKeys[0] = CK_INVALID_HANDLE;
    slot->reason = PK11_DIS_NONE;
    slot->readOnly = PR_TRUE;
    slot->needLogin = PR_FALSE;
    slot->hasRandom = PR_FALSE;
    slot->defRWSession = PR_FALSE;
    slot->protectedAuthPath = PR_FALSE;
    slot->flags = 0;
    slot->session = CK_INVALID_SESSION;
    slot->slotID = 0;
    slot->defaultFlags = 0;
    slot->refCount = 1;
    slot->askpw = 0;
    slot->timeout = 0;
    slot->mechanismList = NULL;
    slot->mechanismCount = 0;
    slot->cert_array = NULL;
    slot->cert_count = 0;
    slot->slot_name[0] = 0;
    slot->token_name[0] = 0;
    PORT_Memset(slot->serial,' ',sizeof(slot->serial));
    slot->module = NULL;
    slot->authTransact = 0;
    slot->authTime = LL_ZERO;
    slot->minPassword = 0;
    slot->maxPassword = 0;
    slot->hasRootCerts = PR_FALSE;
    slot->nssToken = NULL;
    return slot;
}
