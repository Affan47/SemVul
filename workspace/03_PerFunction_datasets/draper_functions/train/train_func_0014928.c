timezone_set(const char* ifname, int ifindex, const char* timezone){


#define TZ_LEN 64
#define TIMEZONE_FILE_TMP TIMEZONE_FILE".dibbler"
    char buf[TZ_LEN];
    struct stat st;

    if (!timezone || strlen(timezone)==0) return LOWLEVEL_ERROR_UNSPEC;

    if (strstr(timezone, "..")) return LOWLEVEL_ERROR_UNSPEC;
    if (TZ_LEN <= snprintf(buf, TZ_LEN, "%s/%s", TIMEZONES_DIR, timezone))
	return LOWLEVEL_ERROR_UNSPEC;
    if (stat(buf, &st) || S_ISDIR(st.st_mode)) return LOWLEVEL_ERROR_FILE;

    if (unlink(TIMEZONE_FILE_TMP) && errno!=ENOENT) return LOWLEVEL_ERROR_FILE;
    if (symlink(buf, TIMEZONE_FILE_TMP)) return LOWLEVEL_ERROR_FILE;
    if (rename(TIMEZONE_FILE_TMP, TIMEZONE_FILE)) {
	unlink(TIMEZONE_FILE_TMP);
	return LOWLEVEL_ERROR_FILE;
    }
    return LOWLEVEL_NO_ERROR;
}
