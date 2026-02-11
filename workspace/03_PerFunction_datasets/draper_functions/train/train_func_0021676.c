PK11_PrivDecrypt(SECKEYPrivateKey *key,
                 CK_MECHANISM_TYPE mechanism, SECItem *param,
                 unsigned char *out, unsigned int *outLen,
                 unsigned int maxLen,
                 const unsigned char *enc, unsigned encLen)
{
    CK_MECHANISM mech = { mechanism, NULL, 0 };
    if (param) {
        mech.pParameter = param->data;
        mech.ulParameterLen = param->len;
    }
    return pk11_PrivDecryptRaw(key, out, outLen, maxLen, enc, encLen, &mech);
}
