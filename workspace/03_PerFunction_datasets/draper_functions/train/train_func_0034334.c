learn_unknown(struct segment_list *sl)
{
  int i;
  for (i = 0; i < sl->nr_segments; i++) {
    struct seg_ent *seg = anthy_get_nth_segment(sl, i);
    struct cand_ent *ce = seg->cands[seg->committed];
    if (ce->nr_words == 0) {
      anthy_add_unknown_word(&seg->str, &ce->str);
    }
  }
}
