__inode_destroy (inode_t *inode)
{
        int          index = 0;
        xlator_t    *xl = NULL;
        xlator_t    *old_THIS = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        if (!inode->_ctx) {
                gf_log (THIS->name, GF_LOG_WARNING, "_ctx not found");
                goto noctx;
        }

        for (index = 0; index < inode->table->ctxcount; index++) {
                if (inode->_ctx[index].xl_key) {
                        xl = (xlator_t *)(long)inode->_ctx[index].xl_key;
                        old_THIS = THIS;
                        THIS = xl;
                        if (xl->cbks->forget)
                                xl->cbks->forget (xl, inode);
                        THIS = old_THIS;
                }
        }

        GF_FREE (inode->_ctx);
noctx:
        LOCK_DESTROY (&inode->lock);

        mem_put (inode);
}
