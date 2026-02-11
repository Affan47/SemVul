SECKEY_DestroyPublicKey(SECKEYPublicKey *pubk)
{
    if (pubk) {
	if (pubk->pkcs11Slot) {
	    if (!PK11_IsPermObject(pubk->pkcs11Slot,pubk->pkcs11ID)) {
		PK11_DestroyObject(pubk->pkcs11Slot,pubk->pkcs11ID);
	    }
	    PK11_FreeSlot(pubk->pkcs11Slot);
	}
    	if (pubk->arena) {
	    PORT_FreeArena(pubk->arena, PR_FALSE);
	}
    }
}
