quota_update_size (xlator_t *this, inode_t *inode, char *name, uuid_t par,
                   int64_t delta)
{
        inode_t           *_inode    = NULL;
        inode_t           *parent    = NULL;
        uint64_t           value     = 0;
        quota_inode_ctx_t *ctx       = NULL;
        uuid_t             trav_uuid = {0,};

        GF_VALIDATE_OR_GOTO ("quota", this, out);
        GF_VALIDATE_OR_GOTO (this->name, inode, out);

        inode_ctx_get (inode, this, &value);
        ctx = (quota_inode_ctx_t *)(unsigned long)value;

        _inode = inode_ref (inode);

        if ( par != NULL ) {
                uuid_copy (trav_uuid, par);
        }

        do {
                if ((ctx != NULL) && (ctx->limit >= 0)) {
                        LOCK (&ctx->lock);
                        {
                                ctx->size += delta;
                        }
                        UNLOCK (&ctx->lock);
                }

                if (__is_root_gfid (_inode->gfid)) {
                        break;
                }

                parent = inode_parent (_inode, trav_uuid, name);
                if (parent == NULL) {
                        gf_log (this->name, GF_LOG_DEBUG,
                                "cannot find parent for inode (gfid:%s), hence "
                                "aborting size updation of parents",
                                uuid_utoa (_inode->gfid));
                }

                if (name != NULL) {
                        name = NULL;
                        uuid_clear (trav_uuid);
                }

                inode_unref (_inode);
                _inode = parent;

                if (_inode == NULL) {
                        break;
                }

                inode_ctx_get (_inode, this, &value);
                ctx = (quota_inode_ctx_t *)(unsigned long)value;
        } while (1);

out:
        return;
}
