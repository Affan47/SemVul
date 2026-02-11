marker_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, fd_t *fd, inode_t *inode,
                   struct iatt *buf, struct iatt *preparent,
                   struct iatt *postparent, dict_t *xdata)
{
        marker_local_t     *local   = NULL;
        marker_conf_t      *priv    = NULL;

        if (op_ret == -1) {
                gf_log (this->name, GF_LOG_TRACE, "error occurred "
                        "while Creating a file %s", strerror (op_errno));
        }

        local = (marker_local_t *) frame->local;

        frame->local = NULL;

        STACK_UNWIND_STRICT (create, frame, op_ret, op_errno, fd, inode, buf,
                             preparent, postparent, xdata);

        if (op_ret == -1 || local == NULL)
                goto out;

        if (uuid_is_null (local->loc.gfid))
                uuid_copy (local->loc.gfid, buf->ia_gfid);

        priv = this->private;

        if (priv->feature_enabled & GF_QUOTA)
                mq_set_inode_xattr (this, &local->loc);

        if (priv->feature_enabled & GF_XTIME)
                marker_xtime_update_marks (this, local);

out:
        marker_local_unref (local);

        return 0;
}
