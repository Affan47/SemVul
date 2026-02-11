sp_inodectx_dump (xlator_t *this, inode_t *inode)
{
        char            key[GF_DUMP_MAX_BUF_LEN]        = {0, };
        char            key_prefix[GF_DUMP_MAX_BUF_LEN] = {0, };
        sp_inode_ctx_t *inode_ctx                       = NULL;
        call_stub_t    *stub                            = NULL;
        uint64_t        value                           = 0;
        int32_t         ret                             = -1, i = 0;

        if ((this == NULL) || (inode == NULL)) {
                goto out;
        }

        ret = inode_ctx_get (inode, this, &value);
        if (ret == 0) {
                inode_ctx = (sp_inode_ctx_t *)(long)value;
        }

        if (inode_ctx == NULL) {
                goto out;
        }

        gf_proc_dump_build_key (key_prefix,
                                "stat-prefetch",
                                "inodectx");
        gf_proc_dump_add_section (key_prefix);

        LOCK (&inode_ctx->lock);
        {
                gf_proc_dump_write ("looked_up", "%s",
                                    inode_ctx->looked_up ? "yes" : "no");

                gf_proc_dump_write ("lookup_in_progress", "%s",
                                    inode_ctx->lookup_in_progress ?
                                    "yes" : "no");

                gf_proc_dump_write ("need_unwind", "%s", inode_ctx->need_unwind ?
                                    "yes" : "no");

                gf_proc_dump_write ("op_ret", "%d", inode_ctx->op_ret);

                gf_proc_dump_write ("op_errno", "%d", inode_ctx->op_errno);

                list_for_each_entry (stub, &inode_ctx->waiting_ops, list) {
                        gf_proc_dump_build_key (key, "",
                                                "waiting-ops[%d].frame", i);
                        gf_proc_dump_write (key, "%"PRId64,
                                            stub->frame->root->unique);

                        gf_proc_dump_build_key (key, "",
                                                "waiting-ops[%d].fop", i);
                        gf_proc_dump_write (key, "%s", gf_fop_list[stub->fop]);

                        i++;
                }
        }
        UNLOCK (&inode_ctx->lock);
out:
        return ret;
}
