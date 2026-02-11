crmf_get_public_value(SECKEYPublicKey *pubKey, SECItem *dest)
{
    SECItem *src;

    switch(pubKey->keyType) {
    case dsaKey:
	src =  &pubKey->u.dsa.publicValue;
	break;
    case rsaKey:
	src =  &pubKey->u.rsa.modulus;
	break;
    case dhKey:
	src =  &pubKey->u.dh.publicValue;
	break;
    default:
	src = NULL;
	break;
    }
    if (!src) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return NULL;
    }

    if (dest != NULL) {
	SECStatus rv = SECITEM_CopyItem(NULL, dest, src);
	if (rv != SECSuccess) {
	    dest = NULL;
	}
    } else {
        dest = SECITEM_ArenaDupItem(NULL, src);
    }
    return dest;
}
