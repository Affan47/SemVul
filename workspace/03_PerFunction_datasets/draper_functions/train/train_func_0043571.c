STAN_InitTokenForSlotInfo(NSSTrustDomain *td, PK11SlotInfo *slot)
{
    NSSToken *token;
    if (!td) {
	td = g_default_trust_domain;
	if (!td) {


	    return PR_SUCCESS;
	}
    }
    token = nssToken_CreateFromPK11SlotInfo(td, slot);
    PK11Slot_SetNSSToken(slot, token);

    if (token) {
	NSSRWLock_LockWrite(td->tokensLock);
	nssList_Add(td->tokenList, token);
	NSSRWLock_UnlockWrite(td->tokensLock);
    }
    return PR_SUCCESS;
}
