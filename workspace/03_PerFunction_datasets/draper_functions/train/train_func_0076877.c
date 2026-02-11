rng_init(void)
{
    PRUint8 bytes[PRNG_SEEDLEN*2];
    unsigned int numBytes;
    SECStatus rv = SECSuccess;

    if (globalrng == NULL) {


	PR_STATIC_ASSERT(sizeof(bytes) >= SHA256_LENGTH);

	globalrng = &theGlobalRng;
        PORT_Assert(NULL == globalrng->lock);

	globalrng->lock = PZ_NewLock(nssILockOther);
	if (globalrng->lock == NULL) {
	    globalrng = NULL;
	    PORT_SetError(PR_OUT_OF_MEMORY_ERROR);
	    return PR_FAILURE;
	}


	numBytes = (unsigned int) RNG_SystemRNG(bytes, sizeof bytes);
	PORT_Assert(numBytes == 0 || numBytes == sizeof bytes);
	if (numBytes != 0) {


	    if (V(globalrng)[0] == 0) {
		rv = prng_instantiate(globalrng, bytes, numBytes);
	    } else {
		rv = prng_reseed_test(globalrng, bytes, numBytes, NULL, 0);
	    }
	    memset(bytes, 0, numBytes);
	} else {
	    PZ_DestroyLock(globalrng->lock);
	    globalrng->lock = NULL;
	    globalrng = NULL;
	    return PR_FAILURE;
	}

	if (rv != SECSuccess) {
	    return PR_FAILURE;
	}

	globalrng->isValid = PR_TRUE;


	prng_generateNewBytes(globalrng, bytes, SHA256_LENGTH, NULL, 0);


	RNG_SystemInfoForRNG();
    }
    return PR_SUCCESS;
}
