ssl2_CipherPrefSetDefault(PRInt32 which, PRBool enabled)
{
    PRUint32     bitMask;

    which &= 0x000f;
    bitMask = 1 << which;

    if (!(bitMask & SSL_CB_IMPLEMENTED)) {
    	PORT_SetError(SSL_ERROR_UNKNOWN_CIPHER_SUITE);
    	return SECFailure;
    }

    if (enabled)
	chosenPreference |= bitMask;
    else
    	chosenPreference &= ~bitMask;
    chosenPreference &= SSL_CB_IMPLEMENTED;

    return SECSuccess;
}
