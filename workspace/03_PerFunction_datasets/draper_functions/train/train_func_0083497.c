rsa_PrivateKeyOpNoCRT(RSAPrivateKey *key, mp_int *m, mp_int *c, mp_int *n,
                      unsigned int modLen)
{
    mp_int d;
    mp_err   err = MP_OKAY;
    SECStatus rv = SECSuccess;
    MP_DIGITS(&d) = 0;
    CHECK_MPI_OK( mp_init(&d) );
    SECITEM_TO_MPINT(key->privateExponent, &d);

    CHECK_MPI_OK( mp_exptmod(c, &d, n, m) );
cleanup:
    mp_clear(&d);
    if (err) {
	MP_TO_SEC_ERROR(err);
	rv = SECFailure;
    }
    return rv;
}
