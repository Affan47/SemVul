badwarn(char *cmd, choice domess, char *arg1, char *arg2, int rc) {
  char *s = "Bad argument in configuration command: ignoring it";
  if (rc == -2)
    warn('C', TRUE, "Bad argument in command line argument %s: ignoring it",
	 cmd);
  else if (rc == -1)
    error("Incorrect default given for %s in anlghead.h", cmd);
  else if (arg2 == NULL)
    warn('C', domess, "%s:\n%s %s", s, cmd, delimit(arg1));
  else
    warn('C', domess, "%s:\n%s %s %s", s, cmd, delimit(arg1), delimit(arg2));
}
