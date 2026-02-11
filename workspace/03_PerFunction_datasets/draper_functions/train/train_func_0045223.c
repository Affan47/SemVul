do_cmd_commit(struct anthy_input_context* ictx)
{
  struct a_segment* as;

  for (as = ictx->segment; as; as = as->next) {
    int len;

    len = anthy_get_segment(ictx->actx, as->index, as->cand, NULL, 0);
    ensure_buffer(&ictx->commit, &ictx->s_commit, ictx->n_commit + len + 1);
    anthy_get_segment(ictx->actx, as->index, as->cand,
		      ictx->commit + ictx->n_commit, len + 1);
    ictx->n_commit += len;
    anthy_commit_segment(ictx->actx, as->index, as->cand);
  }
}
