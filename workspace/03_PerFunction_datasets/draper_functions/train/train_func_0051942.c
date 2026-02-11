compress_clause(Topform c)
{
  if (c->compressed != NULL)
    fatal_error("compress_clause, clause already compressed");
  else if (-MAX_VARS < CHAR_MIN || greatest_symnum() > CHAR_MAX)
    return;
  else if (c->literals == NULL)
    return;
  else {
    Term t = lits_to_term(c->literals);

    c->compressed = compress_term(t);
    free_lits_to_term(t);
    c->neg_compressed = negative_clause(c->literals);
    zap_literals(c->literals);
    c->literals = NULL;
  }
}
