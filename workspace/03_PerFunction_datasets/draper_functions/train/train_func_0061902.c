rsa_PrivateKeyOpCRTCheckedPubKey(RSAPrivateKey *key, mp_int *m, mp_int *c)
{
    mp_int n, e, v;
    mp_err   err = MP_OKAY;
    SECStatus rv = SECSuccess;
    MP_DIGITS(&n) = 0;
    MP_DIGITS(&e) = 0;
    MP_DIGITS(&v) = 0;
    CHECK_MPI_OK( mp_init(&n) );
    CHECK_MPI_OK( mp_init(&e) );
    CHECK_MPI_OK( mp_init(&v) );
    CHECK_SEC_OK( rsa_PrivateKeyOpCRTNoCheck(key, m, c) );
    SECITEM_TO_MPINT(key->modulus,        &n);
    SECITEM_TO_MPINT(key->publicExponent, &e);

    CHECK_MPI_OK( mp_exptmod(m, &e, &n, &v) );
    if (mp_cmp(&v, c) != 0) {
	rv = SECFailure;
    }
cleanup:
    mp_clear(&n);
    mp_clear(&e);
    mp_clear(&v);
    if (err) {
	MP_TO_SEC_ERROR(err);
	rv = SECFailure;
    }
    return rv;
}
