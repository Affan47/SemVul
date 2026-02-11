anthy_commit_prediction(struct anthy_context *ac, int nth)
{
  struct prediction_cache* pc = &ac->prediction;
  if (nth < 0 || nth >= pc->nr_prediction) {
    return -1;
  }
  anthy_do_commit_prediction(pc->predictions[nth].src_str,
			     pc->predictions[nth].str);
  return 0;
}
