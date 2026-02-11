gribskov_conversion_method(block, matrix)
     Block *block;
     Matrix *matrix;
{
  char sijname[SMALL_BUFF_LENGTH], *blimps_dir;
  struct float_qij *sij_matrix;
  FILE *fp;


  blimps_dir = getenv("BLIMPS_DIR");
  if (blimps_dir != NULL)
  {
     sprintf(sijname, "%s/docs/default.sij", blimps_dir);
  }
  else
  {
     sprintf(sijname, "default.sij");
  }

  sij_matrix = load_qij(fp);
  fclose(fp);
  if (sij_matrix == NULL)
  {
      sprintf(ErrorBuffer,
	      "gribskov_conversion_method: default.sij matrix missing, Cannot continue.\n");
      ErrorReport(FATAL_ERR_LVL);
  }


  normalize(block);
  make_gribs(block, matrix, sij_matrix);

}
