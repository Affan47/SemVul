gt_freeSequentialsuffixarrayreader(Sequentialsuffixarrayreader **ssar)
{
  if ((*ssar)->suffixarray != NULL)
  {
    gt_freesuffixarray((*ssar)->suffixarray);
    gt_free((*ssar)->suffixarray);
  }
  gt_freeLcpvalueiterator((*ssar)->lvi);
  gt_free(*ssar);
}
