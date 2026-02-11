ssl2_SetPolicy(PRInt32 which, PRInt32 policy)
{
    PRUint32  bitMask;
    SECStatus rv       = SECSuccess;

    which &= 0x000f;
    bitMask = 1 << which;

    if (!(bitMask & SSL_CB_IMPLEMENTED)) {
    	PORT_SetError(SSL_ERROR_UNKNOWN_CIPHER_SUITE);
    	return SECFailure;
    }

    if (policy == SSL_ALLOWED) {
	allowedByPolicy 	|= bitMask;
	maybeAllowedByPolicy 	|= bitMask;
    } else if (policy == SSL_RESTRICTED) {
    	allowedByPolicy 	&= ~bitMask;
	maybeAllowedByPolicy 	|= bitMask;
    } else {
    	allowedByPolicy 	&= ~bitMask;
    	maybeAllowedByPolicy 	&= ~bitMask;
    }
    allowedByPolicy 		&= SSL_CB_IMPLEMENTED;
    maybeAllowedByPolicy 	&= SSL_CB_IMPLEMENTED;

    policyWasSet = PR_TRUE;
    return rv;
}
