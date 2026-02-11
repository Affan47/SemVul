debug_binaries (const char *subcmd, size_t argc, char *const *const argv)
{
  int r;
  char *out;
  CLEANUP_FREE char *err = NULL;
  char cmd[256];

  snprintf (cmd, sizeof (cmd),
            "%s / -xdev -type f -executable "
            "| %s %s -i "
            "| %s application/x-executable "
            "| %s -F: '{print $1}'",
            str_find, str_xargs, str_file, str_grep, str_gawk);

  r = command (&out, &err, str_sh, "-c", cmd, NULL);
  if (r == -1) {
    reply_with_error ("find: %s", err);
    free (out);
    return NULL;
  }

  return out;
}
