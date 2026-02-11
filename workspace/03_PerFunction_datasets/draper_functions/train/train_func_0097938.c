mq_inspect_file_xattr (xlator_t *this,
                       loc_t *loc,
                       dict_t *dict,
                       struct iatt buf)
{
        int32_t               ret              = -1;
        uint64_t              contri_int       = 0, size = 0;
        int64_t              *contri_ptr       = NULL;
        char                  contri_key [512] = {0, };
        quota_inode_ctx_t    *ctx              = NULL;
        inode_contribution_t *contribution     = NULL;

        ret = mq_inode_ctx_get (loc->inode, this, &ctx);
        if (ret < 0) {
                ctx = mq_inode_ctx_new (loc->inode, this);
                if (ctx == NULL) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "mq_inode_ctx_new failed");
                        ret = -1;
                        goto out;
                }
        }

        contribution = mq_add_new_contribution_node (this, ctx, loc);
        if (contribution == NULL)
                goto out;

        LOCK (&ctx->lock);
        {
                ctx->size = 512 * buf.ia_blocks;
                size = ctx->size;
        }
        UNLOCK (&ctx->lock);

        list_for_each_entry (contribution, &ctx->contribution_head,
                             contri_list) {
                GET_CONTRI_KEY (contri_key, contribution->gfid, ret);
                if (ret < 0)
                        continue;

                ret = dict_get_bin (dict, contri_key, (void **) &contri_int);
                if (ret == 0) {
                        contri_ptr = (int64_t *)(unsigned long)contri_int;

                        LOCK (&contribution->lock);
                        {
                                contribution->contribution = ntoh64 (*contri_ptr);
                                contri_int = contribution->contribution;
                        }
                        UNLOCK (&contribution->lock);

                        gf_log (this->name, GF_LOG_DEBUG,
                                "size=%"PRId64 " contri=%"PRId64, size, contri_int);

                        if (size != contri_int) {
                                mq_initiate_quota_txn (this, loc);
                        }
                } else
                        mq_initiate_quota_txn (this, loc);
        }

out:
        return ret;
}
