set_variable(const char *var, const char *value)
{
  char	comm[1024];

  if (value == NULL || *value == '\0') {
    (void)loc_snprintf(comm, sizeof(comm), "unset %s\n", var);
  }
  else if (bourne_b) {
    (void)loc_snprintf(comm, sizeof(comm), "%s=%s\nexport %s\n",
		       var, value, var);
  }
  else if (rcshell_b) {
    (void)loc_snprintf(comm, sizeof(comm), "%s='%s'\n", var, value);
  }
  else if (gdb_b) {
    (void)loc_snprintf(comm, sizeof(comm), "set env %s %s\n", var, value);
  }
  else {
    (void)loc_snprintf(comm, sizeof(comm), "setenv %s %s\n", var, value);
  }

  if (make_changes_b) {
    (void)printf("%s", comm);
  }
  if ((! make_changes_b) || verbose_b) {
    (void)fprintf(stderr, "Outputed:\n");
    (void)fprintf(stderr, "%s", comm);
  }
}
