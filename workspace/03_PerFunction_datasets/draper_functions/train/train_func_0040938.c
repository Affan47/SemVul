dmg_stripe_zeroes(cli_ctx *ctx, int fd, uint32_t index, struct dmg_mish_with_stripes *mish_set)
{
    int ret = CL_CLEAN;
    size_t len = mish_set->stripes[index].sectorCount * DMG_SECTOR_SIZE;
    ssize_t written;
    uint8_t obuf[BUFSIZ];

    UNUSEDPARAM(ctx);

    cli_dbgmsg("dmg_stripe_zeroes: stripe " STDu32 "\n", index);
    if (len == 0)
        return CL_CLEAN;

    memset(obuf, 0, sizeof(obuf));
    while (len > sizeof(obuf)) {
        written = cli_writen(fd, obuf, sizeof(obuf));
        if ((size_t)written != sizeof(obuf)) {
            ret = CL_EWRITE;
            break;
        }
        len -= sizeof(obuf);
    }

    if ((ret == CL_CLEAN) && (len > 0)) {
        written = cli_writen(fd, obuf, len);
        if ((size_t)written != len) {
            ret = CL_EWRITE;
        }
    }

    if (ret != CL_CLEAN) {
        cli_errmsg("dmg_stripe_zeroes: error writing bytes to file (out of disk space?)\n");
        return CL_EWRITE;
    }
    return CL_CLEAN;
}
