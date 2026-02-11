SetupMAC(CK_MECHANISM_PTR mech, SFTKObject *key)
{
    CK_NSS_MAC_CONSTANT_TIME_PARAMS *params =
	(CK_NSS_MAC_CONSTANT_TIME_PARAMS *) mech->pParameter;
    sftk_MACConstantTimeCtx *ctx;
    HASH_HashType alg;
    SFTKAttribute *keyval;
    unsigned char secret[sizeof(ctx->secret)];
    unsigned int secretLength;

    if (mech->ulParameterLen != sizeof(CK_NSS_MAC_CONSTANT_TIME_PARAMS)) {
	return NULL;
    }

    alg = MACMechanismToHash(params->macAlg);
    if (alg == HASH_AlgNULL) {
	return NULL;
    }

    keyval = sftk_FindAttribute(key,CKA_VALUE);
    if (keyval == NULL) {
	return NULL;
    }
    secretLength = keyval->attrib.ulValueLen;
    if (secretLength > sizeof(secret)) {
	sftk_FreeAttribute(keyval);
	return NULL;
    }
    memcpy(secret, keyval->attrib.pValue, secretLength);
    sftk_FreeAttribute(keyval);

    ctx = PORT_Alloc(sizeof(sftk_MACConstantTimeCtx));
    if (!ctx) {
	return NULL;
    }

    memcpy(ctx->secret, secret, secretLength);
    ctx->secretLength = secretLength;
    ctx->hash = HASH_GetRawHashObject(alg);
    ctx->totalLength = params->ulBodyTotalLen;

    return ctx;
}
