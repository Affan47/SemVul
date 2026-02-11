sb_ivy_write_clause_jmap(String_buf sb, Topform c, I3list map)
{
  if (c->justification->type != IVY_JUST) {
    printf("not ivy just: "); fprint_clause(stdout, c);
    fatal_error("sb_ivy_write_clause_jmap, not IVY_JUST");
  }

  sb_append(sb, "(");
  sb_append_id(sb, c->id, map);
  sb_append(sb, " ");
  sb_ivy_write_just(sb, c->justification->u.ivy, map);
  sb_append(sb, " ");
  sb_ivy_write_literals(sb, c->literals);
  sb_append(sb, " NIL)\n");

}
