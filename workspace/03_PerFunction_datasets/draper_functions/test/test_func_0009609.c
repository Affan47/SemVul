iobref_new ()
{
        struct iobref *iobref = NULL;

        iobref = GF_CALLOC (sizeof (*iobref), 1,
                            gf_common_mt_iobref);
        if (!iobref)
                return NULL;

        LOCK_INIT (&iobref->lock);

        iobref->ref++;

        return iobref;
}
