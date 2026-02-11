HPDF_MMgr_Free  (HPDF_MMgr  mmgr)
{
    HPDF_MPool_Node node;

    HPDF_PTRACE((" HPDF_MMgr_Free\n"));

    if (mmgr == NULL)
        return;

    node = mmgr->mpool;


    while (node != NULL) {
        HPDF_MPool_Node tmp = node;
        node = tmp->next_node;

        HPDF_PTRACE(("-%p mmgr-node-free\n", tmp));


        mmgr->free_fn (tmp);

#ifdef HPDF_MEM_DEBUG
        mmgr->free_cnt++;
#endif

    }

#ifdef HPDF_MEM_DEBUG
    HPDF_PRINTF ("# HPDF_MMgr alloc-cnt=%u, free-cnt=%u\n",
            mmgr->alloc_cnt, mmgr->free_cnt);

    if (mmgr->alloc_cnt != mmgr->free_cnt)
        HPDF_PRINTF ("# ERROR #\n");
#endif

    HPDF_PTRACE(("-%p mmgr-free\n", mmgr));
    mmgr->free_fn (mmgr);


}
