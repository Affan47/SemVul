tty_getf (const char *promptfmt, ... )
{
  va_list arg_ptr;
  char *prompt;
  char *answer;

  va_start (arg_ptr, promptfmt);
  if (estream_vasprintf (&prompt, promptfmt, arg_ptr) < 0)
    log_fatal ("estream_vasprintf failed: %s\n", strerror (errno));
  va_end (arg_ptr);
  answer = tty_get (prompt);
  xfree (prompt);
  return answer;
}
