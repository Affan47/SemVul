compile_voiding_formula (NODE_T * p, FILE_T out, int compose_fun)
{
  if (basic_unit (p)) {
    static char fn[NAME_SIZE];
    char pop[NAME_SIZE];
    (void) make_name (pop, PUP, "", NUMBER (p));
    comment_source (p, out);
    (void) make_name (fn, "_void_formula", "", NUMBER (p));
    if (compose_fun == A68_MAKE_FUNCTION) {
      write_fun_prelude (p, out, fn);
    }
    root_idf = NO_DEC;
    (void) add_declaration (&root_idf, "ADDR_T", 0, pop);
    inline_unit (p, out, L_DECLARE);
    print_declarations (out, root_idf);
    indentf (out, snprintf (line, SNPRINTF_SIZE, "%s = stack_pointer;\n", pop));
    inline_unit (p, out, L_EXECUTE);
    indent (out, "(void) (");
    inline_unit (p, out, L_YIELD);
    undent (out, ");\n");
    indentf (out, snprintf (line, SNPRINTF_SIZE, "stack_pointer = %s;\n", pop));
    if (compose_fun == A68_MAKE_FUNCTION) {
      (void) make_name (fn, "_void_formula", "", NUMBER (p));
      write_fun_postlude (p, out, fn);
    }
    return (fn);
  } else {
    return (NO_TEXT);
  }
}
