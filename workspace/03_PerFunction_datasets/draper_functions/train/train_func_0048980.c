sec_pkcs12_new_asafe(PLArenaPool *poolp)
{
    SEC_PKCS12AuthenticatedSafe  *asafe = NULL;
    void *mark;

    mark = PORT_ArenaMark(poolp);
    asafe = (SEC_PKCS12AuthenticatedSafe *)PORT_ArenaZAlloc(poolp,
	sizeof(SEC_PKCS12AuthenticatedSafe));
    if(asafe == NULL)
	goto loser;
    asafe->poolp = poolp;
    PORT_Memset(&asafe->old_baggage, 0, sizeof(SEC_PKCS12Baggage_OLD));

    PORT_ArenaUnmark(poolp, mark);
    return asafe;

loser:
    PORT_ArenaRelease(poolp, mark);
    return NULL;
}
