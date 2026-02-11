lam_debug_output_low(int lam_debug_id, char *format, va_list arglist)
{
  int len, total_len, want_newline = 0;
  char *str;
  lam_debug_info_t *ldi;


  if (!info_initialized)
    init();


  if (lam_debug_id >= 0 && lam_debug_id < LAM_DEBUG_MAX_STREAMS &&
      info[lam_debug_id].ldi_used == 1 &&
      info[lam_debug_id].ldi_enabled == 1) {
    ldi = &info[lam_debug_id];


#if LAM_HAVE_THREADS
    lam_mutex_lock(&mutex);
#endif
    str = lam_vsnprintf(format, arglist);
    total_len = len = strlen(str);
    if (str[len - 1] != '\n') {
      want_newline = 1;
      ++total_len;
    }
    if (ldi->ldi_prefix != NULL)
      total_len += strlen(ldi->ldi_prefix);
    if (temp_str_len < total_len + want_newline) {
      if (temp_str != NULL)
	free(temp_str);
      temp_str = malloc(total_len * 2);
      temp_str_len = total_len * 2;
    }
    if (ldi->ldi_prefix != NULL) {
      if (want_newline)
	snprintf(temp_str, temp_str_len, "%s%s\n", ldi->ldi_prefix, str);
      else
	snprintf(temp_str, temp_str_len, "%s%s", ldi->ldi_prefix, str);
    } else {
      if (want_newline)
	snprintf(temp_str, temp_str_len, "%s\n", str);
      else
	snprintf(temp_str, temp_str_len, "%s", str);
    }


    if (ldi->ldi_syslog == 1)
      syslog(ldi->ldi_syslog_priority, str);


    if (ldi->ldi_stdout) {
      printf(temp_str);
      fflush(stdout);
    }


    if (ldi->ldi_stderr) {
      fprintf(stderr, temp_str);
      fflush(stderr);
    }


    if (ldi->ldi_fd != -1)
      write(ldi->ldi_fd, temp_str, total_len);
#if LAM_HAVE_THREADS
    lam_mutex_unlock(&mutex);
#endif

    free(str);
  }
}
