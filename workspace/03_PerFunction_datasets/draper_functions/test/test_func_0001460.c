print_query_header (FILE *fp, char initchar, Shortread_T queryseq, bool invertp) {
  fprintf(fp,"%c",initchar);
  if (invertp == false) {
    Shortread_print_oneline(fp,queryseq);
  } else {
    Shortread_print_oneline_revcomp(fp,queryseq);
  }

  return;
}
