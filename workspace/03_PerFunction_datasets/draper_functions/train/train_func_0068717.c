RSA_NewKey(int keySizeInBits, SECItem *publicExponent)
{
    unsigned int primeLen;
    mp_int p, q, e, d;
    int kiter;
    mp_err   err = MP_OKAY;
    SECStatus rv = SECSuccess;
    int prerr = 0;
    RSAPrivateKey *key = NULL;
    PLArenaPool *arena = NULL;

    if (!publicExponent || keySizeInBits % 16 != 0 ||
	    BAD_RSA_KEY_SIZE(keySizeInBits/8, publicExponent->len)) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return NULL;
    }

    arena = PORT_NewArena(NSS_FREEBL_DEFAULT_CHUNKSIZE);
    if (!arena) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	return NULL;
    }
    key = PORT_ArenaZNew(arena, RSAPrivateKey);
    if (!key) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	PORT_FreeArena(arena, PR_TRUE);
	return NULL;
    }
    key->arena = arena;

    primeLen = keySizeInBits / (2 * PR_BITS_PER_BYTE);
    MP_DIGITS(&p) = 0;
    MP_DIGITS(&q) = 0;
    MP_DIGITS(&e) = 0;
    MP_DIGITS(&d) = 0;
    CHECK_MPI_OK( mp_init(&p) );
    CHECK_MPI_OK( mp_init(&q) );
    CHECK_MPI_OK( mp_init(&e) );
    CHECK_MPI_OK( mp_init(&d) );

    SECITEM_AllocItem(arena, &key->version, 1);
    key->version.data[0] = 0;

    SECITEM_TO_MPINT(*publicExponent, &e);
    kiter = 0;
    do {
	prerr = 0;
	PORT_SetError(0);
	CHECK_SEC_OK( generate_prime(&p, primeLen) );
	CHECK_SEC_OK( generate_prime(&q, primeLen) );

	if (mp_cmp(&p, &q) < 0)
	    mp_exch(&p, &q);

	rv = rsa_build_from_primes(&p, &q,
			&e, PR_FALSE,
			&d, PR_TRUE,
			key, keySizeInBits);
	if (rv == SECSuccess)
	    break;
	prerr = PORT_GetError();
	kiter++;

    } while (prerr == SEC_ERROR_NEED_RANDOM && kiter < MAX_KEY_GEN_ATTEMPTS);
    if (prerr)
	goto cleanup;
cleanup:
    mp_clear(&p);
    mp_clear(&q);
    mp_clear(&e);
    mp_clear(&d);
    if (err) {
	MP_TO_SEC_ERROR(err);
	rv = SECFailure;
    }
    if (rv && arena) {
	PORT_FreeArena(arena, PR_TRUE);
	key = NULL;
    }
    return key;
}
