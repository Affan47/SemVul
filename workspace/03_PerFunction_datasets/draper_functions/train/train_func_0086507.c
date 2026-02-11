set_symbol_value(Evaluator *x, char *sym_name)
{
  Symbol *s;

  s = find_symbol_or_create(x, sym_name);
  if (s->is_expr) {
    fprintf(stderr, "Cannot set value for symbol '%s', it is defined by an expression\n");
    exit(2);
  } else {
    s->data.val = 1;
  }
}
