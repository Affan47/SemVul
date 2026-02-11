syncop_listxattr (xlator_t *subvol, loc_t *loc, dict_t **dict)
{
        struct syncargs args = {0, };

        SYNCOP (subvol, (&args), syncop_getxattr_cbk, subvol->fops->getxattr,
                loc, NULL, NULL);

        if (dict)
                *dict = args.xattr;
        else if (args.xattr)
                dict_unref (args.xattr);

        errno = args.op_errno;
        return args.op_ret;
}
