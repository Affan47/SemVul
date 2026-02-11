print_top_ruler (FILE *fp, int n, int npairs, int margin, int wraplength) {
  fprintf(fp,"%*d ",margin,n);
  if (n + wraplength < npairs) {
    fprintf(fp,"%s\n",RULER);
  } else {
    fprintf(fp,"%.*s\n",npairs-n,RULER);
  }
  return;
}
