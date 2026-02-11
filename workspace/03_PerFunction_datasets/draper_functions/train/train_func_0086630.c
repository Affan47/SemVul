anthy_feature_list_set_mw_features(struct feature_list *fl, int mask)
{
  if (mask & MW_FEATURE_WEAK_CONN) {
    anthy_feature_list_add(fl, FEATURE_WEAK);
  }
  if (mask & MW_FEATURE_SUFFIX) {
    anthy_feature_list_add(fl, FEATURE_SUFFIX);
  }
  if (mask & MW_FEATURE_SV) {
    anthy_feature_list_add(fl, FEATURE_SV);
  }
  if (mask & MW_FEATURE_NUM) {
    anthy_feature_list_add(fl, FEATURE_NUM);
  }
  if (mask & MW_FEATURE_CORE1) {
    anthy_feature_list_add(fl, FEATURE_CORE1);
  }
  if (mask & MW_FEATURE_HIGH_FREQ) {
    anthy_feature_list_add(fl, FEATURE_HIGH_FREQ);
  }
  if (mask & MW_FEATURE_WEAK_SEQ) {
    anthy_feature_list_add(fl, FEATURE_WEAK_SEQ);
  }
}
