sftk_RSASignPSS(SFTKHashSignInfo *info, unsigned char *sig,
                unsigned int *sigLen, unsigned int maxLen,
                const unsigned char *hash, unsigned int hashLen)
{
    SECStatus rv = SECFailure;
    HASH_HashType hashAlg;
    HASH_HashType maskHashAlg;
    CK_RSA_PKCS_PSS_PARAMS *params = (CK_RSA_PKCS_PSS_PARAMS *)info->params;

    PORT_Assert(info->key->keyType == NSSLOWKEYRSAKey);
    if (info->key->keyType != NSSLOWKEYRSAKey) {
        PORT_SetError(SEC_ERROR_INVALID_KEY);
        return SECFailure;
    }

    hashAlg = GetHashTypeFromMechanism(params->hashAlg);
    maskHashAlg = GetHashTypeFromMechanism(params->mgf);

    rv = RSA_SignPSS(&info->key->u.rsa, hashAlg, maskHashAlg, NULL,
                     params->sLen, sig, sigLen, maxLen, hash, hashLen);
    if (rv != SECSuccess && PORT_GetError() == SEC_ERROR_LIBRARY_FAILURE) {
        sftk_fatalError = PR_TRUE;
    }
    return rv;
}
