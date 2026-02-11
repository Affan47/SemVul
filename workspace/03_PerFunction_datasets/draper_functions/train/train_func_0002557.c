dht_rename_links_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno,
                      inode_t *inode, struct iatt *stbuf,
                      struct iatt *preparent, struct iatt *postparent)
{
        call_frame_t *prev = NULL;
        dht_local_t  *local = NULL;

        prev = cookie;
        local = frame->local;

        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_WARNING,
                        "link/file %s on %s failed (%s)",
                        local->loc.path, prev->this->name, strerror (op_errno));
        }

        DHT_STACK_DESTROY (frame);

        return 0;
}
