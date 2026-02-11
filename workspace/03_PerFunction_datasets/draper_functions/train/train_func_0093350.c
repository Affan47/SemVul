ra_writev (call_frame_t *frame, xlator_t *this, fd_t *fd, struct iovec *vector,
           int32_t count, off_t offset, struct iobref *iobref)
{
        ra_file_t *file    = NULL;
        uint64_t  tmp_file = 0;
        int32_t   op_errno = EINVAL;

        GF_ASSERT (frame);
        GF_VALIDATE_OR_GOTO (frame->this->name, this, unwind);
        GF_VALIDATE_OR_GOTO (frame->this->name, fd, unwind);

        fd_ctx_get (fd, this, &tmp_file);
        file = (ra_file_t *)(long)tmp_file;
        if (file) {
                flush_region (frame, file, 0, file->pages.prev->offset+1);
                frame->local = file;

                file->expected = file->page_count = 0;
        }

        STACK_WIND (frame, ra_writev_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->writev,
                    fd, vector, count, offset, iobref);

        return 0;

unwind:
        STACK_UNWIND_STRICT (writev, frame, -1, op_errno, NULL, NULL);
        return 0;
}
