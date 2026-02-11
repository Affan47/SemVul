ra_writev_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
               int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
               struct iatt *postbuf, dict_t *xdata)
{
        ra_file_t *file     = NULL;

        GF_ASSERT (frame);

        file = frame->local;

        if (file) {
                flush_region (frame, file, 0, file->pages.prev->offset+1, 1);
        }

        frame->local = NULL;
        STACK_UNWIND_STRICT (writev, frame, op_ret, op_errno, prebuf, postbuf,
                             xdata);
        return 0;
}
