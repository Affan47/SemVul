anthy_feature_list_add(struct feature_list *fl, int f)
{
  if (fl->nr < NR_EM_FEATURES) {
    fl->u.index[fl->nr] = f;
    fl->nr++;
  }
}
