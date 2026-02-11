init (xlator_t *this)
{
        ioc_table_t     *table             = NULL;
        dict_t          *xl_options        = NULL;
        uint32_t         index             = 0;
        int32_t          ret               = -1;
        glusterfs_ctx_t *ctx               = NULL;
        data_t          *data              = 0;

        xl_options = this->options;

        if (!this->children || this->children->next) {
                gf_log (this->name, GF_LOG_ERROR,
                        "FATAL: io-cache not configured with exactly "
                        "one child");
                goto out;
        }

        if (!this->parents) {
                gf_log (this->name, GF_LOG_WARNING,
                        "dangling volume. check volfile ");
        }

        table = (void *) GF_CALLOC (1, sizeof (*table), gf_ioc_mt_ioc_table_t);
        if (table == NULL) {
                gf_log (this->name, GF_LOG_ERROR, "out of memory");
                goto out;
        }

        table->xl = this;
        table->page_size = this->ctx->page_size;

        GF_OPTION_INIT ("cache-size", table->cache_size, size, out);

        GF_OPTION_INIT ("cache-timeout", table->cache_timeout, int32, out);

        GF_OPTION_INIT ("min-file-size", table->min_file_size, size, out);

        GF_OPTION_INIT ("max-file-size", table->max_file_size, size, out);

        if  (!check_cache_size_ok (this, table->cache_size)) {
                ret = -1;
                goto out;
        }

        INIT_LIST_HEAD (&table->priority_list);
        table->max_pri = 1;
        data = dict_get (xl_options, "priority");
        if (data) {
                char *option_list = data_to_str (data);
                gf_log (this->name, GF_LOG_TRACE,
                        "option path %s", option_list);

                table->max_pri = ioc_get_priority_list (option_list,
                                                        &table->priority_list);

                if (table->max_pri == -1) {
                        goto out;
                }
        }
        table->max_pri ++;

        INIT_LIST_HEAD (&table->inodes);

        if ((table->max_file_size >= 0)
            && (table->min_file_size > table->max_file_size)) {
                gf_log ("io-cache", GF_LOG_ERROR, "minimum size (%"
                        PRIu64") of a file that can be cached is "
                        "greater than maximum size (%"PRIu64")",
                        table->min_file_size, table->max_file_size);
                goto out;
        }

        table->inode_lru = GF_CALLOC (table->max_pri,
                                      sizeof (struct list_head),
                                      gf_ioc_mt_list_head);
        if (table->inode_lru == NULL) {
                goto out;
        }

        for (index = 0; index < (table->max_pri); index++)
                INIT_LIST_HEAD (&table->inode_lru[index]);

        pthread_mutex_init (&table->table_lock, NULL);
        this->private = table;
        ret = 0;

        ctx = this->ctx;
        ioc_log2_page_size = log_base2 (ctx->page_size);

out:
        if (ret == -1) {
                if (table != NULL) {
                        GF_FREE (table->inode_lru);
                        GF_FREE (table);
                }
        }

        return ret;
}
