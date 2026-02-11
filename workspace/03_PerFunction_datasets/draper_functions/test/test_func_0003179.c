bash_eval (buffer_t * buf, char *str, size_t len)
{
  static char echo_start[] = "echo -n ";
  static char echo_end[] = "\n";
  if (len == 0)
    return;

  buffer_add (buf, echo_start, strlen (echo_start));
  buffer_add (buf, str, len);
  buffer_add (buf, echo_end, strlen (echo_end));
}
