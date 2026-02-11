wb_sync_cbk (call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
             int32_t op_errno, struct iatt *prebuf, struct iatt *postbuf,
             dict_t *xdata)
{
        wb_local_t   *local             = NULL;
        list_head_t  *winds             = NULL;
        wb_file_t    *file              = NULL;
        wb_request_t *request           = NULL, *dummy = NULL;
        wb_local_t   *per_request_local = NULL;
        int32_t       ret               = -1;
        fd_t         *fd                = NULL;

        GF_ASSERT (frame);
        GF_ASSERT (this);

        local = frame->local;
        winds = &local->winds;

        file = local->file;
        GF_VALIDATE_OR_GOTO (this->name, file, out);

        LOCK (&file->lock);
        {
                list_for_each_entry_safe (request, dummy, winds, winds) {
                        request->flags.write_request.got_reply = 1;

                        if (!request->flags.write_request.write_behind
                            && (op_ret == -1)) {
                                per_request_local = request->stub->frame->local;
                                per_request_local->op_ret = op_ret;
                                per_request_local->op_errno = op_errno;
                        }

                        if (request->flags.write_request.write_behind) {
                                file->window_current -= request->write_size;
                        }

                        __wb_request_unref (request);
                }

                if (op_ret == -1) {
                        file->op_ret = op_ret;
                        file->op_errno = op_errno;
                }
                fd = file->fd;
        }
        UNLOCK (&file->lock);

        ret = wb_process_queue (frame, file);
        if (ret == -1) {
                if (errno == ENOMEM) {
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


        fd_unref (fd);

        STACK_DESTROY (frame->root);

out:
        return 0;
}
