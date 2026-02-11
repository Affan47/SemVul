posix_access (call_frame_t *frame, xlator_t *this,
              loc_t *loc, int32_t mask)
{
        int32_t                 op_ret    = -1;
        int32_t                 op_errno  = 0;
        char                   *real_path = NULL;

        DECLARE_OLD_FS_ID_VAR;
        SET_FS_ID (frame->root->uid, frame->root->gid);

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (loc, out);

        MAKE_REAL_PATH (real_path, this, loc->path);

        op_ret = access (real_path, mask & 07);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR, "access failed on %s: %s",
                        loc->path, strerror (op_errno));
                goto out;
        }
        op_ret = 0;

out:
        SET_TO_OLD_FS_ID ();

        STACK_UNWIND_STRICT (access, frame, op_ret, op_errno);
        return 0;
}
