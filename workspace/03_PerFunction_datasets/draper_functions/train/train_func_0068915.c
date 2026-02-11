trace_writev (call_frame_t *frame, xlator_t *this, fd_t *fd,
              struct iovec *vector, int32_t count,
              off_t offset, struct iobref *iobref)
{
        if (trace_fop_names[GF_FOP_WRITE].enabled) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": gfid=%s fd=%p, count=%d, offset=%"PRId64")",
                        frame->root->unique, uuid_utoa (fd->inode->gfid),
                        fd, count, offset);
                frame->local = fd->inode->gfid;
        }

        STACK_WIND (frame, trace_writev_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->writev,
                    fd, vector, count, offset, iobref);
        return 0;
}
