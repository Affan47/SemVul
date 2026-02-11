print_header_singleend (T this, FILE *fp, Request_T request, bool translocationp, int npaths) {
  Shortread_T queryseq1;

  queryseq1 = Request_queryseq1(request);

  fprintf(fp,">");
  Shortread_print_oneline(fp,queryseq1);
  fprintf(fp,"\t%d",npaths);
  if (translocationp == true) {
    fprintf(fp," (transloc)");
  }


  if (Shortread_quality_string(queryseq1) != NULL) {
    fprintf(fp,"\t");
    Shortread_print_quality(fp,queryseq1,0,0,
			    this->quality_shift,true);
  }

  fprintf(fp,"\t");
  Shortread_print_header(fp,queryseq1);


  return;
}
