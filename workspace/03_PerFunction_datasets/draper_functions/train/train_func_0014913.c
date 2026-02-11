genemap_print_exons (char *annot, Genomicpos_T chroffset, Genome_T genome) {
  char *p;
  char *gbuffer;
  Genomicpos_T exonstart, exonend, exonlow, exonhigh, exonlength;


  p = annot;
  while (*p != '\0' && *p != '\n') {
    putchar(*p);
    p++;
  }
  if (*p == '\n') p++;
  printf("\n");

  while (*p != '\0') {
    if (sscanf(p,"%u %u",&exonstart,&exonend) != 2) {
      fprintf(stderr,"Can't parse exon coordinates in %s\n",p);
      abort();
    } else {
      if (exonstart <= exonend) {
	exonlow = exonstart;
	exonhigh = exonend;
	exonlength = exonhigh - exonlow + 1;
	gbuffer = (char *) CALLOC(exonlength+1,sizeof(char));
	Genome_fill_buffer_simple(genome,chroffset-1U+exonlow,exonlength,gbuffer);
      } else {
	exonlow = exonend;
	exonhigh = exonstart;
	exonlength = exonhigh - exonlow + 1;
	gbuffer = (char *) CALLOC(exonlength+1,sizeof(char));
	Genome_fill_buffer_simple(genome,chroffset-1U+exonlow,exonlength,gbuffer);
	make_complement_inplace(gbuffer,exonlength);
      }
      printf("%s\n",gbuffer);
      FREE(gbuffer);
    }

    while (*p != '\0' && *p != '\n') p++;
    if (*p == '\n') p++;
  }

  return;
}
