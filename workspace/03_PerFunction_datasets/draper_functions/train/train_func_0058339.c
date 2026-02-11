configrepord(void *opt, char *cmd, char *arg1, char *arg2, int rc) {
  extern char repcodes[];
  char *s1 = "REPORTORDER";
  char *s2 = "REPORTORDER in anlghead.h";
  char *s = (rc == -1)?s2:s1;
  choice *order = (choice *)opt;
  logical used[REP_NUMBER];
  int i, j, k;

  if (rc == 0) {
    shortwarn(cmd, arg1, rc);
    return;
  }

  for (i = 0; i < REP_NUMBER; i++)
    used[i] = 0;
  for (i = 0, k = 0; k < REP_NUMBER && arg1[i] != '\0'; i++) {
    if (ISALNUM(arg1[i])) {
      for (j = 0; repcodes[j] != arg1[i] && repcodes[j] != '\0'; j++)
	;
      if (repcodes[j] == '\0')
	warn('C', TRUE, "Spurious character %c in %s: ignoring it", arg1[i],
	     s);
      else if (used[j] == 0) {
	order[k++] = j;
	used[j] = 1;
      }
      else if (used[j] == 1) {
	warn('C', TRUE, "Character %c used more than once in %s: "
	     "ignoring later occurrences", arg1[i], s);
	used[j] = 2;
      }
    }
  }

  if (rc > 1 || arg1[i] != '\0')
    longwarn(cmd, arg1, arg2, rc);

  if (k < REP_NUMBER) {
    for (i = 0; i < REP_NUMBER && k < REP_NUMBER; i++) {
      if (used[i] == 0) {
	warn('C', TRUE, "Character %c not used in %s: adding it at end",
	     repcodes[i], s);
	order[k++] = i;
      }
    }
  }
  order[k] = -1;
}
