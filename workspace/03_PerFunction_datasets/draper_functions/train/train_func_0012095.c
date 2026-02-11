nsspkcs5_NewParam(SECOidTag alg, SECItem *salt, int iterator)
{
    PLArenaPool *arena = NULL;
    NSSPKCS5PBEParameter *pbe_param = NULL;
    SECStatus rv = SECFailure;

    arena = PORT_NewArena(SEC_ASN1_DEFAULT_ARENA_SIZE);
    if (arena == NULL)
	return NULL;


    pbe_param = (NSSPKCS5PBEParameter *)PORT_ArenaZAlloc(arena,
	sizeof(NSSPKCS5PBEParameter));

    if (pbe_param == NULL) {
	goto loser;
    }

    pbe_param->poolp = arena;

    rv = nsspkcs5_FillInParam(alg, pbe_param);
    if (rv != SECSuccess) {
	goto loser;
    }

    pbe_param->iter = iterator;
    if (salt) {
	rv = SECITEM_CopyItem(arena,&pbe_param->salt,salt);
    }


    pbe_param->keyID = pbeBitGenCipherKey;

loser:
    if (rv != SECSuccess) {
	PORT_FreeArena(arena, PR_TRUE);
	pbe_param = NULL;
    }

    return pbe_param;
}
