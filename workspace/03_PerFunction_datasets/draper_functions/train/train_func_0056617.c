mq_get_child_contribution (call_frame_t *frame,
                           void *cookie,
                           xlator_t *this,
                           int32_t op_ret,
                           int32_t op_errno,
                           inode_t *inode,
                           struct iatt *buf,
                           dict_t *dict,
                           struct iatt *postparent)
{
        int32_t        ret                = -1;
        int32_t        val                = 0;
        char           contri_key [512]   = {0, };
        int64_t       *contri             = NULL;
        quota_local_t *local              = NULL;

        local = frame->local;

        frame->local = NULL;

        QUOTA_STACK_DESTROY (frame, this);

        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_ERROR, "%s",
                        strerror (op_errno));
                val = -2;
                if (!mq_test_and_set_local_err (local, &val) &&
                    val != -2)
                        mq_release_lock_on_dirty_inode (local->frame, NULL,
                                                        this, 0, 0, NULL);

                goto exit;
        }

        ret = mq_get_local_err (local, &val);
        if (!ret && val == -2)
                goto exit;

        GET_CONTRI_KEY (contri_key, local->loc.inode->gfid, ret);
        if (ret < 0)
                goto out;

        if (!dict)
                goto out;

        if (dict_get_bin (dict, contri_key, (void **) &contri) == 0)
                local->sum += ntoh64 (*contri);

out:
        LOCK (&local->lock);
        {
                val = --local->dentry_child_count;
        }
        UNLOCK (&local->lock);

        if (val == 0) {
                mq_dirty_inode_readdir (local->frame, NULL, this,
                                        0, 0, NULL, NULL);
        }
        mq_local_unref (this, local);

        return 0;
exit:
        mq_local_unref (this, local);
        return 0;
}
