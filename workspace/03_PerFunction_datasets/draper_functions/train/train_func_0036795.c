wb_fsync (call_frame_t *frame, xlator_t *this, fd_t *fd, int32_t datasync)
{
        wb_file_t    *file     = NULL;
        wb_local_t   *local    = NULL;
        uint64_t      tmp_file = 0;
        call_stub_t  *stub     = NULL;
        wb_request_t *request  = NULL;
        int32_t       ret      = -1, op_errno = 0;

        GF_ASSERT (frame);
        GF_VALIDATE_OR_GOTO_WITH_ERROR (frame->this->name, this, unwind,
                                        op_errno, EINVAL);
        GF_VALIDATE_OR_GOTO_WITH_ERROR (frame->this->name, fd, unwind,
                                        op_errno, EINVAL);


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

        local = GF_CALLOC (1, sizeof (*local), gf_wb_mt_wb_local_t);
        if (local == NULL) {
                op_errno = ENOMEM;
                goto unwind;
        }

        local->file = file;

        frame->local = local;

        if (file) {
                stub = fop_fsync_stub (frame, wb_fsync_helper, fd, datasync);
                if (stub == NULL) {
                        op_errno = ENOMEM;
                        goto unwind;
                }

                request = wb_enqueue (file, stub);
                if (request == NULL) {
                        op_errno = ENOMEM;
                        call_stub_destroy (stub);
                        goto unwind;
                }

                ret = wb_process_queue (frame, file);
                if (ret == -1) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "request queue processing failed");
                }
        } else {
                STACK_WIND (frame, wb_fsync_cbk, FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->fsync, fd, datasync);
        }

        return 0;

unwind:
        STACK_UNWIND_STRICT (fsync, frame, -1, op_errno, NULL, NULL);
        return 0;
}
