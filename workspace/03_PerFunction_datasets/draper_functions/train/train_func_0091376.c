anthy_get_nr_dic_ents(seq_ent_t se, xstr *xs)
{
  struct seq_ent *s = se;
  if (!s) {
    return 0;
  }
  if (!xs) {
    return s->nr_dic_ents;
  }
  return s->nr_dic_ents + anthy_get_nr_dic_ents_of_ext_ent(se, xs);
}
