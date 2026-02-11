generate_blinding_params(RSAPrivateKey *key, mp_int* f, mp_int* g, mp_int *n,
                         unsigned int modLen)
{
    SECStatus rv = SECSuccess;
    mp_int e, k;
    mp_err err = MP_OKAY;
    unsigned char *kb = NULL;

    MP_DIGITS(&e) = 0;
    MP_DIGITS(&k) = 0;
    CHECK_MPI_OK( mp_init(&e) );
    CHECK_MPI_OK( mp_init(&k) );
    SECITEM_TO_MPINT(key->publicExponent, &e);

    kb = PORT_Alloc(modLen);
    if (!kb) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	goto cleanup;
    }
    CHECK_SEC_OK( RNG_GenerateGlobalRandomBytes(kb, modLen) );
    CHECK_MPI_OK( mp_read_unsigned_octets(&k, kb, modLen) );

    CHECK_MPI_OK( mp_mod(&k, n, &k) );

    CHECK_MPI_OK( mp_exptmod(&k, &e, n, f) );

    CHECK_MPI_OK( mp_invmod(&k, n, g) );
cleanup:
    if (kb)
	PORT_ZFree(kb, modLen);
    mp_clear(&k);
    mp_clear(&e);
    if (err) {
	MP_TO_SEC_ERROR(err);
	rv = SECFailure;
    }
    return rv;
}
