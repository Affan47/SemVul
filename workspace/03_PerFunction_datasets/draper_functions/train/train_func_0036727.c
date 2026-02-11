nsc_pbe_key_gen(NSSPKCS5PBEParameter *pkcs5_pbe, CK_MECHANISM_PTR pMechanism,
			void *buf, CK_ULONG *key_length, PRBool faulty3DES)
{
    SECItem *pbe_key = NULL, iv, pwitem;
    CK_PBE_PARAMS *pbe_params = NULL;
    CK_PKCS5_PBKD2_PARAMS *pbkd2_params = NULL;

    *key_length = 0;
    iv.data = NULL; iv.len = 0;

    if (pMechanism->mechanism == CKM_PKCS5_PBKD2) {
	pbkd2_params = (CK_PKCS5_PBKD2_PARAMS *)pMechanism->pParameter;
	pwitem.data = (unsigned char *)pbkd2_params->pPassword;

	pwitem.len = *pbkd2_params->ulPasswordLen;
    } else {
	pbe_params = (CK_PBE_PARAMS *)pMechanism->pParameter;
	pwitem.data = (unsigned char *)pbe_params->pPassword;
	pwitem.len = pbe_params->ulPasswordLen;
    }
    pbe_key = nsspkcs5_ComputeKeyAndIV(pkcs5_pbe, &pwitem, &iv, faulty3DES);
    if (pbe_key == NULL) {
	return CKR_HOST_MEMORY;
    }

    PORT_Memcpy(buf, pbe_key->data, pbe_key->len);
    *key_length = pbe_key->len;
    SECITEM_ZfreeItem(pbe_key, PR_TRUE);
    pbe_key = NULL;

    if (iv.data) {
        if (pbe_params && pbe_params->pInitVector != NULL) {
	    PORT_Memcpy(pbe_params->pInitVector, iv.data, iv.len);
        }
        PORT_Free(iv.data);
    }

    return CKR_OK;
}
