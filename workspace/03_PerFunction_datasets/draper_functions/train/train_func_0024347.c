wb_ftruncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                  struct iatt *postbuf)
{
        wb_local_t   *local   = NULL;
        wb_request_t *request = NULL;
        wb_file_t    *file    = NULL;
        int32_t       ret     = -1;

        GF_ASSERT (frame);

        local = frame->local;
        file = local->file;
        request = local->request;

        if ((request != NULL) && (file != NULL)) {
                wb_request_unref (request);
                ret = wb_process_queue (frame, file);
                if (ret == -1) {
                        if (errno == ENOMEM) {
                                op_ret = -1;
                                op_errno = ENOMEM;
                        }

                        gf_log (this->name, GF_LOG_WARNING,
                                "request queue processing failed");
                }
        }

        STACK_UNWIND_STRICT (ftruncate, frame, op_ret, op_errno, prebuf,
                             postbuf);

        return 0;
}
