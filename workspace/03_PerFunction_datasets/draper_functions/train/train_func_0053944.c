mq_create_dirty_xattr (call_frame_t *frame, void *cookie, xlator_t *this,
                       int32_t op_ret, int32_t op_errno, dict_t *dict)
{
        int32_t          ret       = -1;
        dict_t          *newdict   = NULL;
        quota_local_t   *local     = NULL;

        if (op_ret < 0) {
                goto err;
        }

        local = frame->local;

        if (local->loc.inode->ia_type == IA_IFDIR) {
                newdict = dict_new ();
                if (!newdict) {
                        goto err;
                }

                ret = dict_set_int8 (newdict, QUOTA_DIRTY_KEY, 0);
                if (ret == -1) {
                        goto err;
                }

                STACK_WIND (frame, mq_xattr_creation_release_lock,
                            FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->setxattr,
                            &local->loc, newdict, 0);
        } else {
                mq_xattr_creation_release_lock (frame, NULL, this, 0, 0);
        }

        ret = 0;

err:
        if (ret < 0) {
                mq_xattr_creation_release_lock (frame, NULL, this, 0, 0);
        }

        if (newdict != NULL)
                dict_unref (newdict);

        return 0;
}
