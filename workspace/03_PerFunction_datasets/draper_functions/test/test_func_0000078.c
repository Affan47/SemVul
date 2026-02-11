pileup_func(uint32_t tid, uint32_t position, int n, const bam_pileup1_t *pl, void *data)
{
  tmpstruct_t *tmp = (tmpstruct_t*)data;
  int pos          = (int)position;
  int coverage     = n;
  int i;
  for (i=0;i<n;i++)
    if (pl[i].is_del) coverage--;

  if (tmp->ltid != tid || tmp->lcoverage != coverage || pos > tmp->lpos+1) {
    if (tmp->lpos > 0 && tmp->lcoverage > 0)
      printf("%s\t%d\t%d\t%d\n", tmp->in->header->target_name[tmp->ltid], tmp->lstart,tmp->lpos+1, tmp->lcoverage);
    tmp->ltid       = tid;
    tmp->lstart     = pos;
    tmp->lcoverage  = coverage;
  }
  tmp->lpos = pos;
  return 0;
}
