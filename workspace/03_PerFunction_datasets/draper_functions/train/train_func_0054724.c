posix_readlink (call_frame_t *frame, xlator_t *this,
                loc_t *loc, size_t size, dict_t *xdata)
{
        char *  dest      = NULL;
        int32_t op_ret    = -1;
        int32_t op_errno  = 0;
        char *  real_path = NULL;
        struct iatt stbuf = {0,};

        DECLARE_OLD_FS_ID_VAR;

        VALIDATE_OR_GOTO (frame, out);

        SET_FS_ID (frame->root->uid, frame->root->gid);

        dest = alloca (size + 1);

        MAKE_INODE_HANDLE (real_path, this, loc, &stbuf);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR,
                        "lstat on %s failed: %s", real_path,
                        strerror (op_errno));
                goto out;
        }

        op_ret = readlink (real_path, dest, size);
        if (op_ret == -1) {
                op_errno = errno;
                gf_log (this->name, GF_LOG_ERROR,
                        "readlink on %s failed: %s", real_path,
                        strerror (op_errno));
                goto out;
        }

        dest[op_ret] = 0;
out:
        SET_TO_OLD_FS_ID ();

        STACK_UNWIND_STRICT (readlink, frame, op_ret, op_errno, dest, &stbuf, NULL);

        return 0;
}
