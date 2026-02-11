mq_reduce_parent_size_xattr (call_frame_t *frame, void *cookie,
                             xlator_t *this, int32_t op_ret, int32_t op_errno)
{
        int32_t                  ret               = -1;
        int64_t                 *size              = NULL;
        dict_t                  *dict              = NULL;
        quota_local_t           *local             = NULL;

        local = frame->local;
        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_WARNING,
                        "inodelk set failed on %s", local->parent_loc.path);
                QUOTA_STACK_DESTROY (frame, this);
                return 0;
        }

        VALIDATE_OR_GOTO (local->contri, err);

        dict = dict_new ();
        if (dict == NULL) {
                ret = -1;
                goto err;
        }

        QUOTA_ALLOC_OR_GOTO (size, int64_t, ret, err);

        *size = hton64 (-local->size);

        ret = dict_set_bin (dict, QUOTA_SIZE_KEY, size, 8);
        if (ret < 0)
                goto err;


        STACK_WIND (frame, mq_inode_remove_done, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->xattrop, &local->parent_loc,
                    GF_XATTROP_ADD_ARRAY64, dict);
        dict_unref (dict);
        return 0;

err:
        local->err = 1;
        mq_inode_remove_done (frame, NULL, this, -1, 0, NULL);
        if (dict)
                dict_unref (dict);
        return 0;
}
