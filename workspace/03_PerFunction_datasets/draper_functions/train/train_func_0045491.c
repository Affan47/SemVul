readdirp_rsp_cleanup (gfs3_readdirp_rsp *rsp)
{
        gfs3_dirplist *prev = NULL;
        gfs3_dirplist *trav = NULL;

        trav = rsp->reply;
        prev = trav;
        while (trav) {
                trav = trav->nextentry;
                GF_FREE (prev->dict.dict_val);
                GF_FREE (prev);
                prev = trav;
        }

        return 0;
}
