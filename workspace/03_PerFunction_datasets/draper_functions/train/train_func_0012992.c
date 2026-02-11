gf_proc_dump_xlator_info (xlator_t *top)
{
        xlator_t        *trav = NULL;
        glusterfs_ctx_t *ctx = NULL;
        char             itable_key[1024] = {0,};

        if (!top)
                return;

        ctx = top->ctx;

        trav = top;
        while (trav) {

                if (ctx->measure_latency)
                        gf_proc_dump_latency_info (trav);

                gf_proc_dump_xlator_mem_info(trav);

                if (GF_PROC_DUMP_IS_XL_OPTION_ENABLED (inode) &&
                    (trav->itable)) {
                        snprintf (itable_key, 1024, "%d.%s.itable",
                                  ctx->graph_id, trav->name);
                }

                if (!trav->dumpops) {
                        trav = trav->next;
                        continue;
                }

                if (trav->dumpops->priv &&
                    GF_PROC_DUMP_IS_XL_OPTION_ENABLED (priv))
                        trav->dumpops->priv (trav);

                if (GF_PROC_DUMP_IS_XL_OPTION_ENABLED (inode) &&
                    (trav->dumpops->inode))
                        trav->dumpops->inode (trav);

                if (trav->dumpops->fd &&
                    GF_PROC_DUMP_IS_XL_OPTION_ENABLED (fd))
                        trav->dumpops->fd (trav);

                if (trav->dumpops->history &&
                    GF_PROC_DUMP_IS_XL_OPTION_ENABLED (history))
                        trav->dumpops->history (trav);

                trav = trav->next;
        }

        return;
}
