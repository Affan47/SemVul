dht_unlink_linkfile_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                         int op_ret, int op_errno, struct iatt *preparent,
                         struct iatt *postparent)
{
        dht_local_t  *local = NULL;
        call_frame_t *prev = NULL;

        xlator_t *cached_subvol = NULL;

        local = frame->local;
        prev  = cookie;

        LOCK (&frame->lock);
        {
                if (op_ret == -1) {
                        local->op_errno = op_errno;
                        gf_log (this->name, GF_LOG_DEBUG,
                                "subvolume %s returned -1 (%s)",
                                prev->this->name, strerror (op_errno));
                        goto unlock;
                }

                local->op_ret = 0;
        }
unlock:
        UNLOCK (&frame->lock);

        if (op_ret == -1)
                goto err;

        cached_subvol = dht_subvol_get_cached (this, local->loc.inode);
        if (!cached_subvol) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "no cached subvolume for path=%s",
                        local->loc.path);
                local->op_errno = EINVAL;
                goto err;
        }

        STACK_WIND (frame, dht_unlink_cbk,
                    cached_subvol, cached_subvol->fops->unlink,
                    &local->loc);

        return 0;

err:
        DHT_STACK_UNWIND (unlink, frame, -1, local->op_errno,
                          NULL, NULL);
        return 0;
}
