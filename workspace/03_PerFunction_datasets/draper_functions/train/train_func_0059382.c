xdr_free_exports_list (struct exportnode *first)
{
        struct exportnode       *elist = NULL;

        if (!first)
                return;

        while (first) {
                elist = first->ex_next;
                if (first->ex_dir)
                        GF_FREE (first->ex_dir);

                if (first->ex_groups) {
                        if (first->ex_groups->gr_name)
                                GF_FREE (first->ex_groups->gr_name);
                        GF_FREE (first->ex_groups);
                }

                GF_FREE (first);
                first = elist;
        }

}
