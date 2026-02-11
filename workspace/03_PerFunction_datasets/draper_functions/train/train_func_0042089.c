do_stack(char *name, struct pnode *parms)
{
  struct pnode *p;

  gp_boolean found_size  = false;
  gp_boolean found_ram   = false;
  char *ram_name = NULL;
  struct symbol *sym;

  if (state.has_stack) {
    script_error("multiple stack definitions", NULL);
    return 0;
  } else {
    state.has_stack = true;
  }


  for (; parms != NULL; parms = TAIL(parms)) {
    p = HEAD(parms);
    if ((p->tag == binop) &&
	(p->value.binop.op == '=')) {
      if (enforce_simple(p->value.binop.p0)) {
	char *lhs;

	lhs = p->value.binop.p0->value.symbol;
        if (strcasecmp(lhs, "size") == 0) {
          found_size = true;
          state.stack_size = evaluate(p->value.binop.p1);
        } else if (strcasecmp(lhs, "ram") == 0) {
          if (enforce_simple(p->value.binop.p1)) {
            found_ram = true;
            ram_name = p->value.binop.p1->value.symbol;
          }
        } else {
          script_error("illegal argument", lhs);
        }
      }
    } else {
      if (enforce_simple(p)) {
        script_error("illegal argument", p->value.symbol);
      }
    }
  }


  if (!found_size) {
    script_error("missing argument", "size");
  } else if (ram_name != NULL) {
    sym = add_symbol(state.section.logical, strdup(".stack"));
    annotate_symbol(sym, ram_name);
  }

  return 0;
}
