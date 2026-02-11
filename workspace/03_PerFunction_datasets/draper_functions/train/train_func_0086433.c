pqg_validate_dsa2(unsigned int L, unsigned int N)
{

    switch (L) {
    case 1024:
	if (N != DSA1_Q_BITS) {
	    PORT_SetError(SEC_ERROR_INVALID_ARGS);
	    return SECFailure;
	}
	break;
    case 2048:
	if ((N != 224) && (N != 256)) {
	    PORT_SetError(SEC_ERROR_INVALID_ARGS);
	    return SECFailure;
	}
	break;
    case 3072:
	if (N != 256) {
	    PORT_SetError(SEC_ERROR_INVALID_ARGS);
	    return SECFailure;
	}
	break;
    default:
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }
    return SECSuccess;
}
