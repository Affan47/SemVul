unserialize_rsp_direntp (struct gfs3_readdirp_rsp *rsp, gf_dirent_t *entries)
{
        struct gfs3_dirplist *trav      = NULL;
	gf_dirent_t          *entry     = NULL;
        int                   entry_len = 0;
        int                   ret       = -1;

        trav = rsp->reply;

        while (trav) {
                entry_len = gf_dirent_size (trav->name);
                entry = GF_CALLOC (1, entry_len, gf_common_mt_gf_dirent_t);
                if (!entry)
                        goto out;

                entry->d_ino  = trav->d_ino;
                entry->d_off  = trav->d_off;
                entry->d_len  = trav->d_len;
                entry->d_type = trav->d_type;

                gf_stat_to_iatt (&trav->stat, &entry->d_stat);

                strcpy (entry->d_name, trav->name);

		list_add_tail (&entry->list, &entries->list);

                trav = trav->nextentry;
        }

        ret = 0;
out:
        return ret;
}
