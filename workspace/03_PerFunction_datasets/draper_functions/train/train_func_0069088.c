trace_rchecksum (call_frame_t *frame, xlator_t *this, fd_t *fd, off_t offset,
                 int32_t len, dict_t *xdata)
{
        if (trace_fop_names[GF_FOP_RCHECKSUM].enabled) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": gfid=%s offset=%"PRId64" len=%u fd=%p",
                        frame->root->unique, uuid_utoa (fd->inode->gfid),
                        offset, len, fd);
                frame->local = fd->inode->gfid;
        }

        STACK_WIND (frame, trace_rchecksum_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->rchecksum,
                    fd, offset, len, xdata);

        return 0;

}
