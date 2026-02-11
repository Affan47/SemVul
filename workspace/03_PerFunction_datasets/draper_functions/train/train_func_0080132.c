index_literals(Topform c, Indexop op, Clock clock, BOOL no_fapl)
{
  BOOL unit = (number_of_literals(c->literals) == 1);
  clock_start(clock);
  if (!no_fapl || !positive_clause(c->literals))
    lindex_update(unit ? Unit_fpa_idx : Nonunit_fpa_idx, c, op);

  if (unit)
    lindex_update(Unit_discrim_idx, c, op);
  else {
    Ilist f = features(c->literals);
    if (op == INSERT)
      di_tree_insert(f, Nonunit_features_idx, c);
    else
      di_tree_delete(f, Nonunit_features_idx, c);
    zap_ilist(f);
  }
  clock_stop(clock);
}
