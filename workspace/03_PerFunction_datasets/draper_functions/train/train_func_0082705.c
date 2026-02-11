display_error_message (struct display_error_message_data *d)
{
  if (scm_is_string (d->message) && scm_is_true (scm_list_p (d->args)))
    scm_simple_format (d->port, d->message, d->args);
  else
    scm_display (d->message, d->port);
  scm_newline (d->port);
  return SCM_UNSPECIFIED;
}
