configstrlist(void *opt, char *cmd, char *arg1, char *arg2, int rc) {
  Strlist **list = (Strlist **)opt;
  Strlist *lp = NULL;
  char *t;

  if (rc == 0) {
    shortwarn(cmd, arg1, rc);
    return;
  }
  if (rc == -1)
    t = arg1;
  else if ((t = strtok(arg1, ",")) == NULL) {
    badwarn(cmd, TRUE, arg1, arg2, rc);
    return;
  }
  if (rc > 1)
    longwarn(cmd, arg1, arg2, rc);

  if (*list != NULL) {
    for (lp = *list; lp->next != NULL; TO_NEXT(lp))
      ;
  }
  for ( ; t != NULL; t = ((rc == -1)?NULL:strtok((char *)NULL, ","))) {
    if (strcaseeq(t, "none"))
      *list = NULL;
    else {
      if (*list == NULL) {
	lp = (Strlist *)xmalloc(sizeof(Strlist));
	*list = lp;
      }
      else {
	lp->next = (Strlist *)xmalloc(sizeof(Strlist));
	TO_NEXT(lp);
      }
      if (STREQ(cmd, "DOMCHARTEXPAND") && *t == '.')
	t++;
      COPYSTR(lp->name, t);
      lp->next = NULL;
    }
  }
  return;
}
