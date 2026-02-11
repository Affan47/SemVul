pilFileIsPaf(const char *filename)
{

  FILE *file;
  register int ispaf = 0;
  char paf_record[PAF_RECORD_SIZE + 1];


  if ((file = fopen(filename, "r"))) {
    while (fgets(paf_record, PAF_RECORD_SIZE, file))
      if (!strempty(paf_record, PAF_COMMENT_CHARS))
	if (!strncmp(paf_record, "PAF.HDR.START", 13)) {
	  ispaf = 1;
	  break;
	}

    fclose(file);
  }

  return ispaf;

}
