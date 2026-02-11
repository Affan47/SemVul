print_compopts (cmd, cs, full)
     const char *cmd;
     COMPSPEC *cs;
     int full;
{
  int copts;

  printf ("compopt ");
  copts = cs->options;

  if (full)
    {
      XPRINTCOMPOPT (COPT_BASHDEFAULT, "bashdefault");
      XPRINTCOMPOPT (COPT_DEFAULT, "default");
      XPRINTCOMPOPT (COPT_DIRNAMES, "dirnames");
      XPRINTCOMPOPT (COPT_FILENAMES, "filenames");
      XPRINTCOMPOPT (COPT_NOSPACE, "nospace");
      XPRINTCOMPOPT (COPT_PLUSDIRS, "plusdirs");
    }
  else
    {
      PRINTCOMPOPT (COPT_BASHDEFAULT, "bashdefault");
      PRINTCOMPOPT (COPT_DEFAULT, "default");
      PRINTCOMPOPT (COPT_DIRNAMES, "dirnames");
      PRINTCOMPOPT (COPT_FILENAMES, "filenames");
      PRINTCOMPOPT (COPT_NOSPACE, "nospace");
      PRINTCOMPOPT (COPT_PLUSDIRS, "plusdirs");
    }

  if (STREQ (cmd, EMPTYCMD))
    printf ("-E\n");
  else if (STREQ (cmd, DEFAULTCMD))
    printf ("-D\n");
  else
    printf ("%s\n", cmd);
}
