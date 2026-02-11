check_transformed_clause(struct clause *c,
			      struct clause *orig)
{
  struct clause *d = cl_copy(c);

  process_negative_equalities(d);
  if (!kludgey_e_subsume(d, orig) || !kludgey_e_subsume(orig, d)) {
    printf("%% WARNING: possible error in check_transformed_clause:\n");
    printf("%%    original:    "); p_clause(orig);
    printf("%%    transformed: "); p_clause(d);
  }
}
