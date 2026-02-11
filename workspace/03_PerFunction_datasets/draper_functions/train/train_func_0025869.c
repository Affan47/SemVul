quota_stat (call_frame_t *frame, xlator_t *this, loc_t *loc, dict_t *xdata)
{
        quota_local_t *local = NULL;
        int32_t        ret   = -1;

        local = quota_local_new ();
        if (local == NULL) {
                goto unwind;
        }

        frame->local = local;
        ret = loc_copy (&local->loc, loc);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_WARNING, "loc_copy failed");
                goto unwind;
        }

        STACK_WIND (frame, quota_stat_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->stat, loc, xdata);
        return 0;

unwind:
        QUOTA_STACK_UNWIND (stat, frame, -1, ENOMEM, NULL, NULL);
        return 0;
}
