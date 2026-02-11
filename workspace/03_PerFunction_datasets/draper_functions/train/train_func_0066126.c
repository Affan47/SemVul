SECKEY_CreateDHPrivateKey(SECKEYDHParams *param, SECKEYPublicKey **pubk, void *cx)
{
    SECKEYPrivateKey *privk;
    PK11SlotInfo *slot;

    if (!param || !param->base.data || !param->prime.data ||
        param->prime.len < 512/8 || param->base.len == 0 ||
        param->base.len > param->prime.len + 1 ||
	(param->base.len == 1 && param->base.data[0] == 0)) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return NULL;
    }

    slot = PK11_GetBestSlot(CKM_DH_PKCS_KEY_PAIR_GEN,cx);
    if (!slot) {
	return NULL;
    }

    privk = PK11_GenerateKeyPair(slot, CKM_DH_PKCS_KEY_PAIR_GEN, param,
                                 pubk, PR_FALSE, PR_FALSE, cx);
    if (!privk)
	privk = PK11_GenerateKeyPair(slot, CKM_DH_PKCS_KEY_PAIR_GEN, param,
	                             pubk, PR_FALSE, PR_TRUE, cx);

    PK11_FreeSlot(slot);
    return(privk);
}
