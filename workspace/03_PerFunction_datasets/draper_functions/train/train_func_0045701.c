assign_stringparm(int id, char *val, BOOL echo)
{
  if (id < 0 || id >= Next_stringparm) {
    fprintf(stdout, "assign_stringparm: id %d, is out of range.\n", id);
    fprintf(stderr, "assign_stringparm: id %d, is out of range.\n", id);
    fatal_error("assign_stringparm");
  }
  else {
    struct stringparm *sp = &(Stringparms[id]);
    int i = 0;;

    while (i < sp->n && !str_ident(sp->range[i], val))
      i++;

    if (i < sp->n) {
      sp->val = sp->range[i];
      Option_updates++;
    }
    else {
      printf("range of values for stringparm %s:\n", sp->name);
      for (i = 0; i < sp->n; i++)
	printf("    %s\n", sp->range[i]);
      fatal_error("assign_stringparm, value out of range");
    }
  }
}
