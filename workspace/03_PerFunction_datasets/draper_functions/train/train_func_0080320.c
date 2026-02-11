wb_truncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                 int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                 struct iatt *postbuf, dict_t *xdata)
{
        wb_local_t   *local         = NULL;
        wb_request_t *request       = NULL;
        wb_file_t    *file          = NULL;
        call_frame_t *process_frame = NULL;
        int32_t       ret           = -1;
        fd_t         *fd            = NULL;

        GF_ASSERT (frame);

        local = frame->local;
        file = local->file;
        request = local->request;

        if ((request != NULL) && (file != NULL)) {
                process_frame = copy_frame (frame);
                if (process_frame == NULL) {
                        op_ret = -1;
                        op_errno = ENOMEM;
                }
        }

        STACK_UNWIND_STRICT (truncate, frame, op_ret, op_errno, prebuf,
                             postbuf, xdata);

        if (request) {
                wb_request_unref (request);
        }

        if (process_frame != NULL) {
                ret = wb_process_queue (process_frame, file);
                if (ret == -1) {
                        if ((errno == ENOMEM) && (file != NULL)) {
                                LOCK (&file->lock);
                                {
                                        file->op_ret = -1;
                                        file->op_errno = ENOMEM;
                                }
                                UNLOCK (&file->lock);
                        }

                        gf_log (this->name, GF_LOG_WARNING,
                                "request queue processing failed");
                }

                STACK_DESTROY (process_frame->root);
        }

        if (file) {
                LOCK (&file->lock);
                {
                        fd = file->fd;
                }
                UNLOCK (&file->lock);

                fd_unref (fd);
        }

        return 0;
}
