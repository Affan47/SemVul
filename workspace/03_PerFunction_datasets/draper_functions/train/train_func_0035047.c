glusterfs_xlator_link (xlator_t *pxl, xlator_t *cxl)
{
        xlator_list_t   *xlchild = NULL;
        xlator_list_t   *xlparent = NULL;
        xlator_list_t  **tmp = NULL;

        xlparent = (void *) GF_CALLOC (1, sizeof (*xlparent),
                                       gf_common_mt_xlator_list_t);
        if (!xlparent)
                return -1;

        xlchild = (void *) GF_CALLOC (1, sizeof (*xlchild),
                                      gf_common_mt_xlator_list_t);
        if (!xlchild) {
                GF_FREE (xlparent);

                return -1;
        }

        xlparent->xlator = pxl;
        for (tmp = &cxl->parents; *tmp; tmp = &(*tmp)->next);
        *tmp = xlparent;

        xlchild->xlator = cxl;
        for (tmp = &pxl->children; *tmp; tmp = &(*tmp)->next);
        *tmp = xlchild;

        return 0;
}
