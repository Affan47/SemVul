dsa_NewKeyExtended(const PQGParams *params, const SECItem * seed,
                   DSAPrivateKey **privKey)
{
    mp_int p, g;
    mp_int x, y;
    mp_err err;
    PLArenaPool *arena;
    DSAPrivateKey *key;

    if (!params || !privKey || !seed || !seed->data) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }

    arena = PORT_NewArena(NSS_FREEBL_DSA_DEFAULT_CHUNKSIZE);
    if (!arena) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	return SECFailure;
    }
    key = (DSAPrivateKey *)PORT_ArenaZAlloc(arena, sizeof(DSAPrivateKey));
    if (!key) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	PORT_FreeArena(arena, PR_TRUE);
	return SECFailure;
    }
    key->params.arena = arena;

    MP_DIGITS(&p) = 0;
    MP_DIGITS(&g) = 0;
    MP_DIGITS(&x) = 0;
    MP_DIGITS(&y) = 0;
    CHECK_MPI_OK( mp_init(&p) );
    CHECK_MPI_OK( mp_init(&g) );
    CHECK_MPI_OK( mp_init(&x) );
    CHECK_MPI_OK( mp_init(&y) );

    CHECK_MPI_OK( SECITEM_CopyItem(arena, &key->params.prime,
                                          &params->prime) );
    CHECK_MPI_OK( SECITEM_CopyItem(arena, &key->params.subPrime,
                                          &params->subPrime) );
    CHECK_MPI_OK( SECITEM_CopyItem(arena, &key->params.base, &params->base) );

    SECITEM_TO_MPINT(params->prime, &p);
    SECITEM_TO_MPINT(params->base,  &g);
    OCTETS_TO_MPINT(seed->data, &x, seed->len);

    SECITEM_AllocItem(arena, &key->privateValue, seed->len);
    PORT_Memcpy(key->privateValue.data, seed->data, seed->len);

    CHECK_MPI_OK( mp_exptmod(&g, &x, &p, &y) );

    MPINT_TO_SECITEM(&y, &key->publicValue, arena);
    *privKey = key;
    key = NULL;
cleanup:
    mp_clear(&p);
    mp_clear(&g);
    mp_clear(&x);
    mp_clear(&y);
    if (key)
	PORT_FreeArena(key->params.arena, PR_TRUE);
    if (err) {
	translate_mpi_error(err);
	return SECFailure;
    }
    return SECSuccess;
}
