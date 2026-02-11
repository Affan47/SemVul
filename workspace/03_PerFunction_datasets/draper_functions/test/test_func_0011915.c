pick_new_col(column_sampler *s, int match_cols, double temperature) {
  const int tot_fit = sum_int(s->fits, s->width);
  int r, c;
  set_dbl(s->scores + tot_fit, match_cols, 0);


  r = sample(s->scores, tot_fit + match_cols, temperature);
  for (c = 0; c < s->width; ++c) {
    if (r < s->fits[c])
      break;
    r -= s->fits[c];
  }
  if (c < s->width)
    add_int(s->offsets, s->seq_num, r);
  return c;
}
