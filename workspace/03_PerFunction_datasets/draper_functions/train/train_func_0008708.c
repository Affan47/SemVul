variable_new(struct variable* tail, const char *name, const char *description,
             enum VarType type, ...)
{
  struct variable * v = ergo_new(1, struct variable);
  va_list ap;

  va_start(ap, type);
  v->next = tail;
  v->name = name;
  v->description = description;
  v->type = type;
  switch(type) {
  case VAR_STRING: v->v.str  = strdup(va_arg(ap, char *)); break;
  case VAR_FLOAT:  v->v.num  = va_arg(ap, double);         break;
  case VAR_INT:    v->v.vint = va_arg(ap, int);            break;
  case VAR_LIST:   v->v.list = va_arg(ap, struct variable*); break;
  default: do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "unknown variable type %d\n", type);
  }
  va_end(ap);
  return v;
}
