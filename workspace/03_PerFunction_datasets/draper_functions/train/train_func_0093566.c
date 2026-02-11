output_marker (a2ps_job * job, const char * kind, uchar * marker)
{
  uchar *cp, buf[256];
  int i;

  cp = expand_user_string (job, CURRENT_FILE (job),
			   (const uchar *) kind, marker);

  for (i = 0 ; cp[i] ; i++) {
    switch (cp[i]) {
    case FILE_LAST_PAGE:
      output_delayed_int (jdiv, &(CURRENT_FILE (job)->last_page));
      break;
    case FILE_LAST_SHEET:
      output_delayed_int (jdiv, &(CURRENT_FILE (job)->last_sheet));
      break;
    case FILE_NB_PAGES:
      output_delayed_int (jdiv, &(CURRENT_FILE (job)->pages));
      break;
    case FILE_NB_SHEETS:
      output_delayed_int (jdiv, &(CURRENT_FILE (job)->sheets));
      break;
    case FILE_NB_LINES:
      output_delayed_int (jdiv, &(CURRENT_FILE (job)->lines));
      break;
    case JOB_NB_PAGES:
      output_delayed_int (jdiv, &job->pages);
      break;
    case JOB_NB_SHEETS:
      output_delayed_int (jdiv, &job->sheets);
      break;
    case JOB_NB_FILES:
      output_delayed_int (jdiv, &job->total_files);
      break;
    default:
      *buf = '\0';
      ps_escape_char (job, cp[i], buf);
      output (jdiv, "%s", (char *) buf);
      break;
    }
  }
}
