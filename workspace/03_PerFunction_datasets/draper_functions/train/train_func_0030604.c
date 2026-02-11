CreateOidSequence(void)
{
    CERTOidSequence *rv = (CERTOidSequence *)NULL;
    PLArenaPool *arena = (PLArenaPool *)NULL;

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if( (PLArenaPool *)NULL == arena ) {
        goto loser;
    }

    rv = (CERTOidSequence *)PORT_ArenaZNew(arena, CERTOidSequence);
    if( (CERTOidSequence *)NULL == rv ) {
        goto loser;
    }

    rv->oids = (SECItem **)PORT_ArenaZNew(arena, SECItem *);
    if( (SECItem **)NULL == rv->oids ) {
        goto loser;
    }

    rv->arena = arena;
    return rv;

loser:
    if( (PLArenaPool *)NULL != arena ) {
        PORT_FreeArena(arena, PR_FALSE);
    }

    return (CERTOidSequence *)NULL;
}
