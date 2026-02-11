posix_truncate (call_frame_t *frame, xlator_t *this, loc_t *loc, off_t offset)
{
        int32_t               op_ret    = -1;
        int32_t               op_errno  = 0;
        char                 *real_path = 0;
        struct posix_private *priv      = NULL;
        struct iatt           prebuf    = {0,};
        struct iatt           postbuf   = {0,};

        DECLARE_OLD_FS_ID_VAR;

        VALIDATE_OR_GOTO (frame, out);
        VALIDATE_OR_GOTO (this, out);
        VALIDATE_OR_GOTO (loc, out);

        priv = this->private;
        VALIDATE_OR_GOTO (priv, out);

        SET_FS_ID (frame->root->uid, frame->root->gid);

        MAKE_INODE_HANDLE (real_path, this, loc, &prebuf);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR,
                        "pre-operation lstat on %s failed: %s",
                        real_path, strerror (op_errno));
                goto out;
        }

        op_ret = truncate (real_path, offset);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR,
                        "truncate on %s failed: %s",
                        real_path, strerror (op_errno));
                goto out;
        }

        op_ret = posix_pstat (this, loc->gfid, real_path, &postbuf);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR, "lstat on %s failed: %s",
                        real_path, strerror (op_errno));
                goto out;
        }

        op_ret = 0;

out:
        SET_TO_OLD_FS_ID ();

        STACK_UNWIND_STRICT (truncate, frame, op_ret, op_errno,
                             &prebuf, &postbuf);

        return 0;
}
