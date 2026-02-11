anthy_has_non_compound_ents(seq_ent_t se)
{
  if (!se) {
    return 0;
  }
  if (se->nr_dic_ents == 0) {
    return 1;
  }
  return se->nr_dic_ents - se->nr_compound_ents;
}
