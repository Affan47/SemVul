afr_get_locks_fd_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, struct gf_flock *lock)
{
        if (op_ret) {
                gf_log (this->name, GF_LOG_INFO,
                        "Failed to get locks on fd");
                goto cleanup;
        }

        gf_log (this->name, GF_LOG_DEBUG,
                "Got a lock on fd");

        if (is_afr_lock_eol (lock)) {
                gf_log (this->name, GF_LOG_INFO,
                        "Reached EOL on locks on fd");
                goto cleanup;
        }

        afr_recover_lock (frame, this, lock);

        return 0;

cleanup:
        afr_lock_recovery_cleanup (frame, this);

        return 0;
}
