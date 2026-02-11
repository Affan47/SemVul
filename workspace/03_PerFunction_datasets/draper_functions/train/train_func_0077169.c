__ioc_page_create (ioc_inode_t *ioc_inode, off_t offset)
{
        ioc_table_t *table          = NULL;
        ioc_page_t  *page           = NULL;
        off_t        rounded_offset = 0;
        ioc_page_t  *newpage        = NULL;

        GF_VALIDATE_OR_GOTO ("io-cache", ioc_inode, out);

        table = ioc_inode->table;
        GF_VALIDATE_OR_GOTO ("io-cache", table, out);

        rounded_offset = floor (offset, table->page_size);

        newpage = GF_CALLOC (1, sizeof (*newpage), gf_ioc_mt_ioc_newpage_t);
        if (newpage == NULL) {
                goto out;
        }

        if (!ioc_inode) {
                GF_FREE (newpage);
                newpage = NULL;
                goto out;
        }

        newpage->offset = rounded_offset;
        newpage->inode = ioc_inode;
        pthread_mutex_init (&newpage->page_lock, NULL);

        rbthash_insert (ioc_inode->cache.page_table, newpage, &rounded_offset,
                        sizeof (rounded_offset));

        list_add_tail (&newpage->page_lru, &ioc_inode->cache.page_lru);

        page = newpage;

        gf_log ("io-cache", GF_LOG_TRACE,
                "returning new page %p", page);

out:
        return page;
}
