wb_flush_helper (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *xdata)
{
        wb_conf_t    *conf        = NULL;
        wb_local_t   *local       = NULL;
        wb_file_t    *file        = NULL;
        call_frame_t *flush_frame = NULL, *process_frame = NULL;
        int32_t       op_ret      = -1, op_errno = -1, ret = -1;

        GF_ASSERT (frame);
        GF_VALIDATE_OR_GOTO_WITH_ERROR (frame->this->name, this, unwind,
                                        op_errno, EINVAL);

        conf = this->private;

        local = frame->local;
        file = local->file;

        LOCK (&file->lock);
        {
                op_ret = file->op_ret;
                op_errno = file->op_errno;
        }
        UNLOCK (&file->lock);

        if (local && local->request) {
                process_frame = copy_frame (frame);
                if (process_frame == NULL) {
                        op_errno = ENOMEM;
                        goto unwind;
                }

                wb_request_unref (local->request);
        }

        if (conf->flush_behind) {
                flush_frame = copy_frame (frame);
                if (flush_frame == NULL) {
                        op_errno = ENOMEM;
                        goto unwind;
                }

                STACK_WIND (flush_frame, wb_ffr_bg_cbk, FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->flush, fd, xdata);
        } else {
                STACK_WIND (frame, wb_ffr_cbk, FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->flush, fd, xdata);
        }

        if (process_frame != NULL) {
                ret = wb_process_queue (process_frame, file);
                if (ret == -1) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "request queue processing failed");
                }

                STACK_DESTROY (process_frame->root);
        }

        if (conf->flush_behind) {
                STACK_UNWIND_STRICT (flush, frame, op_ret, op_errno, NULL);
        }

        return 0;

unwind:
        STACK_UNWIND_STRICT (flush, frame, -1, op_errno, NULL);
        return 0;
}
