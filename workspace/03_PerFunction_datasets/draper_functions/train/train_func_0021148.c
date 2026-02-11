anthy_release_cand_ent(struct cand_ent *ce)
{
  if (ce->elm) {
    free(ce->elm);
  }
  if (&ce->str) {
    anthy_free_xstr_str(&ce->str);
  }
  free(ce);
}
