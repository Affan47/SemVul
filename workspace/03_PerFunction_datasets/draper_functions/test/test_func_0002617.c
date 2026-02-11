commit_ochaire(struct seg_ent *seg, int count, xstr* xs)
{
  int i;
  if (xs->len >= MAX_OCHAIRE_LEN) {
    return ;
  }
  if (anthy_select_row(xs, 1)) {
    return ;
  }
  anthy_set_nth_value(0, count);
  for (i = 0; i < count; i++, seg = seg->next) {
    anthy_set_nth_value(i * 2 + 1, seg->len);
    anthy_set_nth_xstr(i * 2 + 2, &seg->cands[seg->committed]->str);
  }
}
