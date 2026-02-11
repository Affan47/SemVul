syncop_readlink (xlator_t *subvol, loc_t *loc, char **buffer, size_t size)
{
        struct syncargs args = {0, };

        SYNCOP (subvol, (&args), syncop_readlink_cbk, subvol->fops->readlink,
                loc, size, NULL);

        if (buffer)
                *buffer = args.buffer;
        else GF_FREE (args.buffer);

        errno = args.op_errno;
        return args.op_ret;
}
