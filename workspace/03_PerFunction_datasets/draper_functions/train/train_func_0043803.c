__wb_inode_create (xlator_t *this, inode_t *inode)
{
        wb_inode_t *wb_inode = NULL;
        wb_conf_t  *conf     = NULL;

        GF_VALIDATE_OR_GOTO (this->name, inode, out);

        conf = this->private;

        wb_inode = GF_CALLOC (1, sizeof (*wb_inode), gf_wb_mt_wb_inode_t);
        if (!wb_inode)
                goto out;

        INIT_LIST_HEAD (&wb_inode->all);
        INIT_LIST_HEAD (&wb_inode->todo);
        INIT_LIST_HEAD (&wb_inode->liability);
        INIT_LIST_HEAD (&wb_inode->temptation);
        INIT_LIST_HEAD (&wb_inode->wip);

        wb_inode->this = this;

        wb_inode->window_conf = conf->window_size;

        LOCK_INIT (&wb_inode->lock);

        __inode_ctx_put (inode, this, (uint64_t)(unsigned long)wb_inode);

out:
        return wb_inode;
}
