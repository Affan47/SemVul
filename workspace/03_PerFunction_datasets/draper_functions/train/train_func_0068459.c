wb_flush (call_frame_t *frame, xlator_t *this, fd_t *fd)
{
        wb_conf_t    *conf        = NULL;
        wb_file_t    *file        = NULL;
        wb_local_t   *local       = NULL;
        uint64_t      tmp_file    = 0;
        call_stub_t  *stub        = NULL;
        call_frame_t *flush_frame = NULL;
        wb_request_t *request     = NULL;
        int32_t       ret         = 0, op_errno = 0;

        GF_ASSERT (frame);
        GF_VALIDATE_OR_GOTO_WITH_ERROR (frame->this->name, this, unwind,
                                        op_errno, EINVAL);
        GF_VALIDATE_OR_GOTO_WITH_ERROR (this->name, fd, unwind, op_errno,
                                        EINVAL);

        conf = this->private;


        if ((!IA_ISDIR (fd->inode->ia_type))
            && fd_ctx_get (fd, this, &tmp_file)) {
                file = wb_file_create (this, fd, 0);
        } else {
                file = (wb_file_t *)(long)tmp_file;
                if ((!IA_ISDIR (fd->inode->ia_type)) && (file == NULL)) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "wb_file not found for fd %p", fd);
                        op_errno = EBADFD;
                        goto unwind;
                }
        }

        if (file != NULL) {
                local = GF_CALLOC (1, sizeof (*local), gf_wb_mt_wb_local_t);
                if (local == NULL) {
                        op_errno = ENOMEM;
                        goto unwind;
                }

                local->file = file;

                frame->local = local;

                stub = fop_flush_stub (frame, wb_flush_helper, fd);
                if (stub == NULL) {
                        op_errno = ENOMEM;
                        goto unwind;
                }

                request = wb_enqueue (file, stub);
                if (request == NULL) {
                        call_stub_destroy (stub);
                        op_errno = ENOMEM;
                        goto unwind;
                }

                ret = wb_process_queue (frame, file);
                if (ret == -1) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "request queue processing failed");
                }
        } else {
                if (conf->flush_behind) {
                        flush_frame = copy_frame (frame);
                        if (flush_frame == NULL) {
                                op_errno = ENOMEM;
                                goto unwind;
                        }

                        STACK_UNWIND_STRICT (flush, frame, 0, 0);

                        STACK_WIND (flush_frame, wb_ffr_bg_cbk,
                                    FIRST_CHILD(this),
                                    FIRST_CHILD(this)->fops->flush, fd);
                } else {
                        STACK_WIND (frame, wb_ffr_cbk, FIRST_CHILD(this),
                                    FIRST_CHILD(this)->fops->flush, fd);
                }
        }

        return 0;

unwind:
        STACK_UNWIND_STRICT (flush, frame, -1, op_errno);
        return 0;
}
