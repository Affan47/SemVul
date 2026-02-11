or_state_save_broken(char *fname)
{
  int i;
  file_status_t status;
  char *fname2 = NULL;
  for (i = 0; i < 100; ++i) {
    tor_asprintf(&fname2, "%s.%d", fname, i);
    status = file_status(fname2);
    if (status == FN_NOENT)
      break;
    tor_free(fname2);
  }
  if (i == 100) {
    log_warn(LD_BUG, "Unable to parse state in \"%s\"; too many saved bad "
             "state files to move aside. Discarding the old state file.",
             fname);
    unlink(fname);
  } else {
    log_warn(LD_BUG, "Unable to parse state in \"%s\". Moving it aside "
             "to \"%s\".  This could be a bug in Tor; please tell "
             "the developers.", fname, fname2);
    if (rename(fname, fname2) < 0) {
      log_warn(LD_BUG, "Weirdly, I couldn't even move the state aside. The "
               "OS gave an error of %s", strerror(errno));
    }
  }
  tor_free(fname2);
}
