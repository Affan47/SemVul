mq_check_n_set_inode_xattr (call_frame_t *frame, void *cookie,
                            xlator_t *this, int32_t op_ret, int32_t op_errno,
                            inode_t *inode, struct iatt *buf, dict_t *dict,
                            struct iatt *postparent)
{
        quota_local_t        *local           = NULL;
        int64_t              *size            = NULL, *contri = NULL;
        int8_t                dirty           = 0;
        int32_t               ret             = 0;
        char                  contri_key[512] = {0, };

        if (op_ret < 0) {
                goto out;
        }

        local = frame->local;

        ret = dict_get_bin (dict, QUOTA_SIZE_KEY, (void **) &size);
        if (ret < 0)
                goto create_xattr;

        ret = dict_get_int8 (dict, QUOTA_DIRTY_KEY, &dirty);
        if (ret < 0)
                goto create_xattr;


        if (strcmp (local->loc.path, "/") != 0) {
                GET_CONTRI_KEY (contri_key, local->loc.parent->gfid, ret);
                if (ret < 0)
                        goto out;

                ret = dict_get_bin (dict, contri_key, (void **) &contri);
                if (ret < 0)
                        goto create_xattr;
        }

out:
        mq_xattr_creation_release_lock (frame, NULL, this, 0, 0, NULL);
        return 0;

create_xattr:
        if (uuid_is_null (local->loc.gfid)) {
                uuid_copy (local->loc.gfid, buf->ia_gfid);
        }

        mq_create_xattr (this, frame);
        return 0;
}
