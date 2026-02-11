ioc_mknod (call_frame_t *frame, xlator_t *this, loc_t *loc, mode_t mode,
           dev_t rdev, mode_t umask, dict_t *xdata)
{
        ioc_local_t *local    = NULL;
        int32_t      op_errno = -1, ret = -1;

        local = mem_get0 (this->local_pool);
        if (local == NULL) {
                op_errno = ENOMEM;
                gf_log (this->name, GF_LOG_ERROR, "out of memory");
                goto unwind;
        }

        ret = loc_copy (&local->file_loc, loc);
        if (ret != 0) {
                op_errno = ENOMEM;
                gf_log (this->name, GF_LOG_ERROR, "out of memory");
                goto unwind;
        }

        frame->local = local;

        STACK_WIND (frame, ioc_mknod_cbk,
                    FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->mknod,
                    loc, mode, rdev, umask, xdata);
        return 0;

unwind:
        if (local != NULL) {
                loc_wipe (&local->file_loc);
                mem_put (local);
        }

        STACK_UNWIND_STRICT (mknod, frame, -1, op_errno, NULL, NULL,
                             NULL, NULL, NULL);

        return 0;
}
