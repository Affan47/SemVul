dfa_cp_output_rawdata(FILE *fp, DFA_INFO *dfa)
{
  int i, j;

  for(i=0;i<dfa->term_num;i++) {
    fprintf(fp, "%d:", i);
    for(j=0;j<dfa->cplen[i];j++) {
      fprintf(fp, " %d", dfa->cp[i][j]);
    }
    fprintf(fp, "\n");
  }
  fprintf(fp, "bgn:");
  for(j=0;j<dfa->cp_begin_len;j++) {
    fprintf(fp, " %d", dfa->cp_begin[j]);
  }
  fprintf(fp, "\n");
  fprintf(fp, "end:");
  for(j=0;j<dfa->cp_end_len;j++) {
    fprintf(fp, " %d", dfa->cp_end[j]);
  }
  fprintf(fp, "\n");
}
