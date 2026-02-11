crmf_copy_cert_name(PLArenaPool *poolp, CERTName **dest,
		    CERTName *src)
{
    CERTName *newName;
    SECStatus rv;
    void     *mark;

    mark = PORT_ArenaMark(poolp);
    *dest = newName = PORT_ArenaZNew(poolp, CERTName);
    if (newName == NULL) {
        goto loser;
    }

    rv = CERT_CopyName(poolp, newName, src);
    if (rv != SECSuccess) {
      goto loser;
    }
    PORT_ArenaUnmark(poolp, mark);
    return SECSuccess;
 loser:
    PORT_ArenaRelease(poolp, mark);
    *dest = NULL;
    return SECFailure;
}
