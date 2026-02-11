posix_removexattr (call_frame_t *frame, xlator_t *this,
                   loc_t *loc, const char *name, dict_t *xdata)
{
        int32_t op_ret    = -1;
        int32_t op_errno  = 0;
        char *  real_path = NULL;

        DECLARE_OLD_FS_ID_VAR;

        MAKE_INODE_HANDLE (real_path, this, loc, NULL);

        if (!strcmp (GFID_XATTR_KEY, name)) {
                gf_log (this->name, GF_LOG_WARNING, "Remove xattr called"
                        " on gfid for file %s", real_path);
                op_ret = -1;
                goto out;
        }


        SET_FS_ID (frame->root->uid, frame->root->gid);

        op_ret = sys_lremovexattr (real_path, name);
        if (op_ret == -1) {
                op_errno = errno;
                if (op_errno != ENOATTR && op_errno != EPERM)
                        gf_log (this->name, GF_LOG_ERROR,
                                "removexattr on %s (for %s): %s", real_path,
                                name, strerror (op_errno));
                goto out;
        }

        op_ret = 0;

out:
        SET_TO_OLD_FS_ID ();

        STACK_UNWIND_STRICT (removexattr, frame, op_ret, op_errno, NULL);
        return 0;
}
