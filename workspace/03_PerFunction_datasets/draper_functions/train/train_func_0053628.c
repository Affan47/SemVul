DH_Derive(SECItem *publicValue,
          SECItem *prime,
          SECItem *privateValue,
          SECItem *derivedSecret,
          unsigned int outBytes)
{
    mp_int p, Xa, Yb, ZZ, psub1;
    mp_err err = MP_OKAY;
    int len = 0;
    unsigned int nb;
    unsigned char *secret = NULL;
    if (!publicValue || !prime || !privateValue || !derivedSecret) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }
    memset(derivedSecret, 0, sizeof *derivedSecret);
    MP_DIGITS(&p)  = 0;
    MP_DIGITS(&Xa) = 0;
    MP_DIGITS(&Yb) = 0;
    MP_DIGITS(&ZZ) = 0;
    MP_DIGITS(&psub1) = 0;
    CHECK_MPI_OK( mp_init(&p)  );
    CHECK_MPI_OK( mp_init(&Xa) );
    CHECK_MPI_OK( mp_init(&Yb) );
    CHECK_MPI_OK( mp_init(&ZZ) );
    CHECK_MPI_OK( mp_init(&psub1) );
    SECITEM_TO_MPINT(*publicValue,  &Yb);
    SECITEM_TO_MPINT(*privateValue, &Xa);
    SECITEM_TO_MPINT(*prime,        &p);
    CHECK_MPI_OK( mp_sub_d(&p, 1, &psub1) );


    if (mp_cmp_d(&Yb, 1) <= 0 ||
	mp_cmp(&Yb, &psub1) >= 0) {
	err = MP_BADARG;
	goto cleanup;
    }


    CHECK_MPI_OK( mp_exptmod(&Yb, &Xa, &p, &ZZ) );

    len = mp_unsigned_octet_size(&ZZ);
    if (len <= 0) {
        err = MP_BADARG;
        goto cleanup;
    }

    secret = PORT_Alloc(len);

    err = mp_to_unsigned_octets(&ZZ, secret, len);
    if (err >= 0) err = MP_OKAY;


    if (outBytes > 0)
	nb = outBytes;
    else
	nb = len;
    SECITEM_AllocItem(NULL, derivedSecret, nb);
    if (len < nb) {
	unsigned int offset = nb - len;
	memset(derivedSecret->data, 0, offset);
	memcpy(derivedSecret->data + offset, secret, len);
    } else {
	memcpy(derivedSecret->data, secret + len - nb, nb);
    }
cleanup:
    mp_clear(&p);
    mp_clear(&Xa);
    mp_clear(&Yb);
    mp_clear(&ZZ);
    mp_clear(&psub1);
    if (secret) {

	PORT_ZFree(secret, len);
    }
    if (err) {
	MP_TO_SEC_ERROR(err);
	if (derivedSecret->data)
	    PORT_ZFree(derivedSecret->data, derivedSecret->len);
	return SECFailure;
    }
    return SECSuccess;
}
