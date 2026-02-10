merge_identical_invariants (void)
{
  unsigned i;
  struct invariant *inv;
  htab_t eq = htab_create (VEC_length (invariant_p, invariants),
			   hash_invariant_expr, eq_invariant_expr, free);

  FOR_EACH_VEC_ELT (invariant_p, invariants, i, inv)
    find_identical_invariants (eq, inv);

  htab_delete (eq);
}
