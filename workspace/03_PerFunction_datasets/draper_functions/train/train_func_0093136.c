read_quant_tables (j_compress_ptr cinfo, char * filename, boolean force_baseline)


{
  FILE * fp;
  int tblno, i, termchar;
  long val;
  unsigned int table[DCTSIZE2];

  if ((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Can't open table file %s\n", filename);
    return FALSE;
  }
  tblno = 0;

  while (read_text_integer(fp, &val, &termchar)) {
    if (tblno >= NUM_QUANT_TBLS) {
      fprintf(stderr, "Too many tables in file %s\n", filename);
      fclose(fp);
      return FALSE;
    }
    table[0] = (unsigned int) val;
    for (i = 1; i < DCTSIZE2; i++) {
      if (! read_text_integer(fp, &val, &termchar)) {
	fprintf(stderr, "Invalid table data in file %s\n", filename);
	fclose(fp);
	return FALSE;
      }
      table[i] = (unsigned int) val;
    }
    jpeg_add_quant_table(cinfo, tblno, table, cinfo->q_scale_factor[tblno],
			 force_baseline);
    tblno++;
  }

  if (termchar != EOF) {
    fprintf(stderr, "Non-numeric data in file %s\n", filename);
    fclose(fp);
    return FALSE;
  }

  fclose(fp);
  return TRUE;
}
