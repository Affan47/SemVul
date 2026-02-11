put_htk_hmm(FILE *fp, HTK_HMM_Data *h)
{
  int i;

  if (fp == NULL) return;
  fprintf(fp, "name: %s\n", h->name);
  fprintf(fp, "state num: %d\n", h->state_num);
  for (i=0;i<h->state_num;i++) {
    fprintf(fp, "**** state %d ****\n",i+1);
    put_htk_state(fp, h->s[i]);
  }
  put_htk_trans(fp, h->tr);
}
