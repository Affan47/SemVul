quota_symlink (call_frame_t *frame, xlator_t *this, const char *linkpath,
               loc_t *loc, mode_t umask, dict_t *xdata)
{
        int32_t          ret      = -1;
        int32_t          op_errno = ENOMEM;
        quota_local_t   *local    = NULL;
        call_stub_t     *stub     = NULL;

        local = quota_local_new ();
        if (local == NULL) {
                goto err;
        }

        frame->local = local;

        ret = loc_copy (&local->loc, loc);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_WARNING, "loc_copy failed");
                goto err;
        }

        local->link_count = 1;

        stub = fop_symlink_stub (frame, quota_symlink_helper, linkpath, loc,
                                 umask, xdata);
        if (stub == NULL) {
                goto err;
        }

        local->stub = stub;
        local->delta = strlen (linkpath);

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
        QUOTA_STACK_UNWIND (symlink, frame, -1, op_errno, NULL, NULL, NULL,
                            NULL, NULL);

        return 0;
}
