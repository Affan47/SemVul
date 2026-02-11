dht_linkfile_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                         int op_ret, int op_errno, inode_t *inode,
                         struct iatt *stbuf, struct iatt *preparent,
                         struct iatt *postparent, dict_t *xdata)
{
        dht_local_t  *local = NULL;

        local = frame->local;

        if (!op_ret)
                local->linked = _gf_true;

        local->linkfile.linkfile_cbk (frame, cookie, this, op_ret, op_errno,
                                      inode, stbuf, preparent, postparent,
                                      xdata);
        return 0;
}
