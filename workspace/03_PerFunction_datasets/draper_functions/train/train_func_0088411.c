remove_file_if_very_old(const char *fname, time_t now)
{
#define VERY_OLD_FILE_AGE (28*24*60*60)
  struct stat st;

  if (stat(fname, &st)==0 && st.st_mtime < now-VERY_OLD_FILE_AGE) {
    char buf[ISO_TIME_LEN+1];
    format_local_iso_time(buf, st.st_mtime);
    log_notice(LD_GENERAL, "Obsolete file %s hasn't been modified since %s. "
               "Removing it.", fname, buf);
    unlink(fname);
  }
}
