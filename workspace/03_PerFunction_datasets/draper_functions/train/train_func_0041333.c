storeUfsDirCloseTmpSwapLog(SwapDir * sd)
{
    ufsinfo_t *ufsinfo = (ufsinfo_t *) sd->fsdata;
    char *swaplog_path = xstrdup(storeUfsDirSwapLogFile(sd, NULL));
    char *new_path = xstrdup(storeUfsDirSwapLogFile(sd, ".new"));
    int fd;
    file_close(ufsinfo->swaplog_fd);
    if (xrename(new_path, swaplog_path) < 0) {
	fatal("storeUfsDirCloseTmpSwapLog: rename failed");
    }
    fd = file_open(swaplog_path, O_WRONLY | O_CREAT | O_BINARY);
    if (fd < 0) {
	debug(50, 1) ("%s: %s\n", swaplog_path, xstrerror());
	fatal("storeUfsDirCloseTmpSwapLog: Failed to open swap log.");
    }
    safe_free(swaplog_path);
    safe_free(new_path);
    ufsinfo->swaplog_fd = fd;
    debug(47, 3) ("Cache Dir #%d log opened on FD %d\n", sd->index, fd);
}
