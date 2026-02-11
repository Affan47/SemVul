storeUfsDirOpenTmpSwapLog(SwapDir * sd, int *clean_flag, int *zero_flag)
{
    ufsinfo_t *ufsinfo = (ufsinfo_t *) sd->fsdata;
    char *swaplog_path = xstrdup(storeUfsDirSwapLogFile(sd, NULL));
    char *clean_path = xstrdup(storeUfsDirSwapLogFile(sd, ".last-clean"));
    char *new_path = xstrdup(storeUfsDirSwapLogFile(sd, ".new"));
    struct stat log_sb;
    struct stat clean_sb;
    FILE *fp;
    int fd;
    if (stat(swaplog_path, &log_sb) < 0) {
	debug(47, 1) ("Cache Dir #%d: No log file\n", sd->index);
	safe_free(swaplog_path);
	safe_free(clean_path);
	safe_free(new_path);
	return NULL;
    }
    *zero_flag = log_sb.st_size == 0 ? 1 : 0;

    if (ufsinfo->swaplog_fd >= 0)
	file_close(ufsinfo->swaplog_fd);

    fd = file_open(new_path, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY);
    if (fd < 0) {
	debug(50, 1) ("%s: %s\n", new_path, xstrerror());
	fatal("storeDirOpenTmpSwapLog: Failed to open swap log.");
    }
    ufsinfo->swaplog_fd = fd;
    storeUfsWriteSwapLogheader(fd);

    fp = fopen(swaplog_path, "rb");
    if (fp == NULL) {
	debug(50, 0) ("%s: %s\n", swaplog_path, xstrerror());
	fatal("Failed to open swap log for reading");
    }
    memset(&clean_sb, '\0', sizeof(struct stat));
    if (stat(clean_path, &clean_sb) < 0)
	*clean_flag = 0;
    else if (clean_sb.st_mtime < log_sb.st_mtime)
	*clean_flag = 0;
    else
	*clean_flag = 1;
    safeunlink(clean_path, 1);
    safe_free(swaplog_path);
    safe_free(clean_path);
    safe_free(new_path);
    return fp;
}
