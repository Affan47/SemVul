syncop_fgetxattr (xlator_t *subvol, fd_t *fd, dict_t **dict, const char *key)
{
        struct syncargs args = {0, };

        SYNCOP (subvol, (&args), syncop_getxattr_cbk, subvol->fops->fgetxattr,
                fd, key);

        if (dict)
                *dict = args.xattr;
        else if (args.xattr)
                dict_unref (args.xattr);

        errno = args.op_errno;
        return args.op_ret;
}
