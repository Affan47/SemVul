confirm_exit (void)
{
  char *cmd;
  int k;
  ASSERT (snprintf (output_line, SNPRINTF_SIZE, "Terminate %s (yes|no): ", a68g_cmd_name) >= 0);
  WRITELN (STDOUT_FILENO, output_line);
  cmd = read_string_from_tty (NULL);
  if (TO_UCHAR (cmd[0]) == TO_UCHAR (EOF_CHAR)) {
    return (confirm_exit ());
  }
  for (k = 0; cmd[k] != NULL_CHAR; k++) {
    cmd[k] = (char) TO_LOWER (cmd[k]);
  }
  if (strcmp (cmd, "y") == 0) {
    return (A68_TRUE);
  }
  if (strcmp (cmd, "yes") == 0) {
    return (A68_TRUE);
  }
  if (strcmp (cmd, "n") == 0) {
    return (A68_FALSE);
  }
  if (strcmp (cmd, "no") == 0) {
    return (A68_FALSE);
  }
  return (confirm_exit ());
}
