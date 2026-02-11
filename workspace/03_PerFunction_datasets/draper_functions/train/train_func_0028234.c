merge_identical_invariants (void)
{
  unsigned i;
  struct invariant *inv;
  htab_t eq = htab_create (invariants.length (),
			   hash_invariant_expr, eq_invariant_expr, free);

  FOR_EACH_VEC_ELT (invariants, i, inv)
    find_identical_invariants (eq, inv);

  htab_delete (eq);
}
