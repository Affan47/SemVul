MOOVar_new_float(const char *d) {
  char *s = NULL;
  double f = strtod(d, &s);
  MOOVar *var;

  if (!(s && !*s)) {
    return NULL;
  }

  var = g_malloc(sizeof(MOOVar));
  var->type = FLOAT;
  var->s = NULL;
  var->i = 0;
  var->d = f;
  var->list = NULL;
  var->next = NULL;
  return var;
}
