find_next_command_separator(World *world, const char *cmdline)
{
  int  pos            = 0;
  int  len            = strlen(cmdline);
  char quote          = 0;
  int  cmdseplen      = strlen(world->command_separator);
  gboolean use_quotes = FALSE;

  if (cmdline[0] == '/'
      && len > 1 && cmdline[1] != '/') {
    use_quotes = TRUE;
  }

  while (pos < len) {
    if (use_quotes && (cmdline[pos] == '\"' || cmdline[pos] == '\'')) {
      if (quote) {
        if (cmdline[pos] == quote && cmdline[pos-1] != '\\') {
          quote = 0;
        }
      } else {
        if (pos == 0 || cmdline[pos-1] != '\\') {
          quote = cmdline[pos];
        }
      }

    } else if (cmdline[pos] == world->command_separator[0]) {
      if (!quote && pos != (len - (cmdseplen-1))
          && strncmp(cmdline + pos, world->command_separator,
                     cmdseplen) == 0) {
        return pos;
      }
    }

    ++pos;
  }

  return -1;
}
