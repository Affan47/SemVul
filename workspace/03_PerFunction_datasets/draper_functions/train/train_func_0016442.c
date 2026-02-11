get_diag_matrix_from_file(int n,
			  symmMatrix & M,
			  const char* fileName,
			  std::vector<int> const & permutationHML)
{
  std::vector<ergo_real> diagonalValues(n);
  std::vector<int> rowind(n);
  std::vector<int> colind(n);

  FILE* f = fopen(fileName, "rt");
  if(f == NULL)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error opening file '%s'", fileName);
      return -1;
    }

  const int BUFSIZE = 888888;
  std::vector<char> buf(BUFSIZE);
  memset(&buf[0], 0, BUFSIZE * sizeof(char));

  int nBytes = (int)fread(&buf[0], sizeof(char), BUFSIZE, f);
  fclose(f);
  if(nBytes <= 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error reading file '%s'", fileName);
      return -1;
    }
  if(nBytes >= (BUFSIZE-1000))
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error in get_diag_matrix_from_file: input file too large");
      return -1;
    }

  do_output(LOG_CAT_INFO, LOG_AREA_MAIN, "get_diag_matrix_from_file: File '%s' read OK, nBytes = %i", fileName, nBytes);

  int i = 0;
  char* p = &buf[0];
  while(*p != '\0')
    {

      if(i >= n)
	{
	  do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error in get_diag_matrix_from_file: too many lines in file.");
	  return -1;
	}


      while(*p == ' ' || *p == '\t')
	p++;

      diagonalValues[i] = atof(p);
      i++;


      while(*p != '\n' && *p != '\0')
	p++;
      p++;
    }

  for(i = 0; i < n; i++)
    {
      rowind[i] = i;
      colind[i] = i;
    }
  do_output(LOG_CAT_INFO, LOG_AREA_SCF, "get_diag_matrix_from_file: calling densityMatrix.assign_from_sparse.");
  M.assign_from_sparse(rowind,
		       colind,
		       diagonalValues,
		       permutationHML,
		       permutationHML);
  do_output(LOG_CAT_INFO, LOG_AREA_SCF, "get_diag_matrix_from_file: densityMatrix.assign_from_sparse returned.");

  return 0;
}
