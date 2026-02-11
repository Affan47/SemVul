mq_inodelk_cbk (call_frame_t *frame, void *cookie,
                xlator_t *this, int32_t op_ret, int32_t op_errno)
{
        int32_t         ret    = 0;
        gf_boolean_t    status = _gf_false;
        quota_local_t  *local  = NULL;

        local = frame->local;

        if (op_ret == -1 || local->err) {
                if (op_ret == -1) {
                        gf_log (this->name, GF_LOG_DEBUG,
                                "unlocking failed on path (%s)(%s)",
                                local->parent_loc.path, strerror (op_errno));
                }
                mq_xattr_updation_done (frame, NULL, this, 0, 0, NULL);

                return 0;
        }

        gf_log (this->name, GF_LOG_DEBUG,
                "inodelk released on %s", local->parent_loc.path);

        if ((strcmp (local->parent_loc.path, "/") == 0)
            || (local->delta == 0)) {
                mq_xattr_updation_done (frame, NULL, this, 0, 0, NULL);
        } else {
                ret = mq_get_parent_inode_local (this, local);
                if (ret < 0) {
                        mq_xattr_updation_done (frame, NULL, this, 0, 0, NULL);
                        goto out;
                }
                status = _gf_true;

                ret = mq_test_and_set_ctx_updation_status (local->ctx, &status);
                if (ret == 0 && status == _gf_false) {
                        mq_get_lock_on_parent (frame, this);
                } else {
                        mq_xattr_updation_done (frame, NULL, this, 0, 0, NULL);
                }
        }
out:
        return 0;
}
