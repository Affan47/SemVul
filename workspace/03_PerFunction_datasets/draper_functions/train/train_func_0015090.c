log_fragments(GtFragment *fragments, unsigned long num_of_fragments)
{
  unsigned long i;
  gt_log_log("show chaining fragments");
  for (i = 0; i < num_of_fragments; i++) {
    GtFragment *frag = fragments + i;
    gt_log_log("#%lu: s1=%lu, s1=%lu, l1=%lu, s2=%lu, e2=%lu, l2=%lu, w=%lu", i,
            frag->startpos1, frag->endpos1, frag->endpos1 - frag->startpos1 + 1,
            frag->startpos2, frag->endpos2, frag->endpos2 - frag->startpos2 + 1,
            frag->weight);
  }
}
