dht_linkfile_unlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                         int32_t op_ret, int32_t op_errno,
                         struct iatt *preparent, struct iatt *postparent)
{
        dht_local_t   *local = NULL;
        call_frame_t  *prev = NULL;
        xlator_t      *subvol = NULL;

        local = frame->local;
        prev = cookie;
        subvol = prev->this;

        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_INFO,
                        "unlinking linkfile %s on %s failed (%s)",
                        local->loc.path, subvol->name, strerror (op_errno));
        }

        DHT_STACK_DESTROY (frame);

        return 0;
}
