rewritable_top(Flatterm f)
{
  if (ARITY(f) == 0)
    return FALSE;
  else {
    Context subst = get_context();
    Discrim_pos dpos;
    Term t = discrim_flat_retrieve_first(f, Demod_index->discrim_tree, subst, &dpos);
    if (t)
      discrim_flat_cancel(dpos);
    free_context(subst);
    return t != NULL;
  }
}
