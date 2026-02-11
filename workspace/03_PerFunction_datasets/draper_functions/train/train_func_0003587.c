configallchart(void *opt, char *cmd, char *arg1, char *arg2, int rc) {

  choice *q = (choice *)opt;
  choice p = UNSET;
  int i;

  if (rc == 0) {
    shortwarn(cmd, arg1, rc);
    return;
  }
  if (rc > 1)
    longwarn(cmd, arg1, arg2, rc);

  if (strcaseeq(arg1, "ON") || strcaseeq(arg1, "TRUE") ||
      strcaseeq(arg1, "SORTBY"))
    p = CHART_SORTBY;
  else if (strcaseeq(arg1, "OFF") || strcaseeq(arg1, "FALSE") ||
	   strcaseeq(arg1, "NONE"))
    p = CHART_NONE;

 if (p == UNSET)
    badwarn(cmd, TRUE, arg1, arg2, rc);
  else for (i = 0; i < GENREP_NUMBER; i++)
    q[i] = p;
}
