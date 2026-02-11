quota_mkdir (call_frame_t *frame, xlator_t *this, loc_t *loc, mode_t mode,
             dict_t *params)
{
        int32_t        ret            = 0, op_errno = 0;
        quota_local_t *local          = NULL;
        call_stub_t   *stub           = NULL;

        local = quota_local_new ();
        if (local == NULL) {
                op_errno = ENOMEM;
                goto err;
        }

        frame->local = local;

        local->link_count = 1;

        ret = loc_copy (&local->loc, loc);
        if (ret) {
                op_errno = ENOMEM;
                gf_log (this->name, GF_LOG_WARNING, "loc_copy failed");
                goto err;
        }

        stub = fop_mkdir_stub (frame, quota_mkdir_helper, loc, mode, params);
        if (stub == NULL) {
                op_errno = ENOMEM;
                goto err;
        }

        local->stub = stub;
        local->delta = 0;

        quota_check_limit (frame, loc->parent, this, NULL, NULL);

        stub = NULL;

        LOCK (&local->lock);
        {
                if (local->validate_count == 0) {
                        stub = local->stub;
                        local->stub = NULL;
                }

                local->link_count = 0;
        }
        UNLOCK (&local->lock);

        if (stub != NULL) {
                call_resume (stub);
        }

        return 0;
err:
        QUOTA_STACK_UNWIND (mkdir, frame, -1, op_errno, NULL, NULL, NULL,
                            NULL);

        return 0;
}
