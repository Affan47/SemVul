sp_lookup_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
               int32_t op_ret, int32_t op_errno, inode_t *inode,
               struct iatt *buf, dict_t *dict, struct iatt *postparent)
{
        struct list_head     waiting_ops = {0, };
        call_stub_t         *stub        = NULL, *tmp = NULL;
        sp_local_t          *local       = NULL;
        int                  need_unwind = 0;
        char                 looked_up   = 0, lookup_in_progress = 0;

        GF_ASSERT (frame);

        INIT_LIST_HEAD (&waiting_ops);

        local = frame->local;
        if (local == NULL) {
                op_ret = -1;
                op_errno = EINVAL;
                gf_log (this->name, GF_LOG_WARNING, "local is NULL, but it is "
                        "needed to find and resume operations waiting on "
                        "lookup");
                goto out;
        }

        if (this == NULL) {
                op_ret = -1;
                op_errno = EINVAL;
                gf_log (frame->this ? frame->this->name : "stat-prefetch",
                        GF_LOG_WARNING, "xlator object (this) is NULL");
                goto out;
        }


        if ((op_ret == -1) && local->loc.parent) {
                sp_remove_caches_from_all_fds_opened (this, local->loc.parent,
                                                      (char *)local->loc.name);
        }

        if (local->is_lookup)
                need_unwind = 1;

        lookup_in_progress = 0;
        looked_up = 1;
        sp_update_inode_ctx (this, local->loc.inode, &op_ret, &op_errno,
                             &lookup_in_progress, &looked_up, buf,
                             &waiting_ops, &op_errno);

        list_for_each_entry_safe (stub, tmp, &waiting_ops, list) {
                list_del_init (&stub->list);
                call_resume (stub);
        }

out:
        if (need_unwind) {
                SP_STACK_UNWIND (lookup, frame, op_ret, op_errno, inode, buf,
                                 dict, postparent);
        }

        return 0;
}
