lam_debug_open(lam_debug_stream_info_t *lds)
{
  int i;
  int flags;
  char *filename;


  if (lds->lds_fl_debug != 0 && LAM_WANT_DEBUG == 0)
    return LAMERROR;


  if (!info_initialized)
    init();


  for (i = 0; i < LAM_DEBUG_MAX_STREAMS; ++i)
    if (info[i].ldi_used == 0)
      break;
  if (i >= LAM_DEBUG_MAX_STREAMS)
    return LAMERROR;


  info[i].ldi_used = 1;
  info[i].ldi_enabled = lds->lds_fl_debug ? LAM_WANT_DEBUG : 1;

  info[i].ldi_syslog = lds->lds_fl_syslog;
  if (lds->lds_fl_syslog == 1) {
    if (lds->lds_syslog_ident != NULL) {
      info[i].ldi_syslog_ident = strdup(lds->lds_syslog_ident);
      openlog(lds->lds_syslog_ident, LOG_PID, LOG_USER);
    } else {
      info[i].ldi_syslog_ident = NULL;
      openlog("lam", LOG_PID, LOG_USER);
    }
    info[i].ldi_syslog_priority = lds->lds_syslog_priority;
  }

  if (lds->lds_prefix != NULL) {
    info[i].ldi_prefix = strdup(lds->lds_prefix);
    info[i].ldi_prefix_len = strlen(lds->lds_prefix);
  } else {
    info[i].ldi_prefix = NULL;
    info[i].ldi_prefix_len = 0;
  }

  info[i].ldi_stdout = lds->lds_fl_stdout;
  info[i].ldi_stderr = lds->lds_fl_stderr;

  info[i].ldi_fd = -1;
  if (lds->lds_fl_file == 1) {


    filename = lam_get_tmpdir();
    strcat(filename, "/lam-");
    if (lds->lds_file_suffix != NULL) {
      info[i].ldi_file_suffix = strdup(lds->lds_file_suffix);
      strcat(filename, lds->lds_file_suffix);
    } else {
      info[i].ldi_file_suffix = NULL;
      strcat(filename, "debug.txt");
    }
    flags = O_CREAT | O_RDWR;
    if (!lds->lds_fl_file_append)
      flags |= O_TRUNC;


    info[i].ldi_fd = open(filename, flags, 0644);
    if (info[i].ldi_fd == -1) {
      info[i].ldi_used = 0;
      return LAMERROR;
    }


    fcntl(info[i].ldi_fd, F_SETFD, 1);
    free(filename);
  }

  return i;
}
