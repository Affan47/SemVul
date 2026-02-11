showhelp(char *who, char *file, struct flag_record *flags, int fl)
{
  int lines = 0;
  char s[HELP_BUF_LEN + 1];
  FILE *f = resolve_help(fl, file);

  if (f) {
    help_subst(NULL, NULL, 0, HELP_IRC, NULL);
    while (!feof(f)) {
      fgets(s, HELP_BUF_LEN, f);
      if (!feof(f)) {
        if (s[strlen(s) - 1] == '\n')
          s[strlen(s) - 1] = 0;
        if (!s[0])
          strcpy(s, " ");
        help_subst(s, who, flags, 0, file);
        if ((s[0]) && (strlen(s) > 1)) {
          dprintf(DP_HELP, "NOTICE %s :%s\n", who, s);
          lines++;
        }
      }
    }
    fclose(f);
  }
  if (!lines && !(fl & HELP_TEXT))
    dprintf(DP_HELP, "NOTICE %s :%s\n", who, IRC_NOHELP2);
}
