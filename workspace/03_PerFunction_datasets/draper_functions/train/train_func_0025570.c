STAN_RemoveModuleFromDefaultTrustDomain (
  SECMODModule *module
)
{
    NSSToken *token;
    NSSTrustDomain *td;
    int i;
    td = STAN_GetDefaultTrustDomain();
    NSSRWLock_LockWrite(td->tokensLock);
    for (i=0; i<module->slotCount; i++) {
	token = PK11Slot_GetNSSToken(module->slots[i]);
	if (token) {
	    nssToken_NotifyCertsNotVisible(token);
	    nssList_Remove(td->tokenList, token);
	    PK11Slot_SetNSSToken(module->slots[i], NULL);
	    nssToken_Destroy(token);
 	}
    }
    nssListIterator_Destroy(td->tokens);
    td->tokens = nssList_CreateIterator(td->tokenList);
    NSSRWLock_UnlockWrite(td->tokensLock);
    return SECSuccess;
}
