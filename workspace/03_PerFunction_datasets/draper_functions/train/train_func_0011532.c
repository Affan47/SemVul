__ioc_inode_waitq_dump (ioc_inode_t *ioc_inode, char *prefix)
{
        ioc_waitq_t *trav                     = NULL;
        ioc_page_t  *page                     = NULL;
        int32_t      i                        = 0;
        char         key[GF_DUMP_MAX_BUF_LEN] = {0, };

        trav = ioc_inode->waitq;

        while (trav) {
                page = trav->data;

                sprintf (key, "cache-validation-waitq.page[%d].offset", i++);
                gf_proc_dump_write (key, "%"PRId64, page->offset);

                trav = trav->next;
        }
}
