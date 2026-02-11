DH_NewKey(DHParams *params, DHPrivateKey **privKey)
{
    PLArenaPool *arena;
    DHPrivateKey *key;
    mp_int g, xa, p, Ya;
    mp_err   err = MP_OKAY;
    SECStatus rv = SECSuccess;
    if (!params || !privKey) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }
    arena = PORT_NewArena(NSS_FREEBL_DEFAULT_CHUNKSIZE);
    if (!arena) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	return SECFailure;
    }
    key = (DHPrivateKey *)PORT_ArenaZAlloc(arena, sizeof(DHPrivateKey));
    if (!key) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	PORT_FreeArena(arena, PR_TRUE);
	return SECFailure;
    }
    key->arena = arena;
    MP_DIGITS(&g)  = 0;
    MP_DIGITS(&xa) = 0;
    MP_DIGITS(&p)  = 0;
    MP_DIGITS(&Ya) = 0;
    CHECK_MPI_OK( mp_init(&g)  );
    CHECK_MPI_OK( mp_init(&xa) );
    CHECK_MPI_OK( mp_init(&p)  );
    CHECK_MPI_OK( mp_init(&Ya) );

    CHECK_SEC_OK( SECITEM_CopyItem(arena, &key->prime, &params->prime) );
    SECITEM_TO_MPINT(key->prime, &p);

    CHECK_SEC_OK( SECITEM_CopyItem(arena, &key->base, &params->base) );
    SECITEM_TO_MPINT(key->base, &g);

    SECITEM_AllocItem(arena, &key->privateValue,
                      dh_GetSecretKeyLen(params->prime.len));
    RNG_GenerateGlobalRandomBytes(key->privateValue.data,
                                  key->privateValue.len);
    SECITEM_TO_MPINT( key->privateValue, &xa );

    CHECK_MPI_OK( mp_mod(&xa, &p, &xa) );

    CHECK_MPI_OK( mp_exptmod(&g, &xa, &p, &Ya) );
    MPINT_TO_SECITEM(&Ya, &key->publicValue, key->arena);
    *privKey = key;
cleanup:
    mp_clear(&g);
    mp_clear(&xa);
    mp_clear(&p);
    mp_clear(&Ya);
    if (err) {
	MP_TO_SEC_ERROR(err);
	rv = SECFailure;
    }
    if (rv)
	PORT_FreeArena(arena, PR_TRUE);
    return rv;
}
