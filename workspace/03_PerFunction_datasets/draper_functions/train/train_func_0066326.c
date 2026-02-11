load_density_and_project_full(const char *densityFileName,
			      int noOfDensityMatrices,
			      const IntegralInfo* integralInfo,
			      const BasisInfoStruct & basisInfo,
			      ergo_real** densityMatrixList,
			      int do_purification,
			      const int* noOfElectronsList,
			      ergo_real electronic_temperature)
{
  int n = basisInfo.noOfBasisFuncs;
  ergo_real* densityMatrixListForStartingGuess[2];
  BasisInfoStruct* basisInfoStartingGuess = NULL;

  if(ddf_load_density(densityFileName, noOfDensityMatrices,
                      *integralInfo, &basisInfoStartingGuess,
                      densityMatrixListForStartingGuess) != 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error in ddf_load_density");
      return -1;
    }


  int n_sg = basisInfoStartingGuess->noOfBasisFuncs;
  ergo_real* R = ergo_new(n*n_sg, ergo_real);
  do_output(LOG_CAT_INFO, LOG_AREA_MAIN, "calling compute_overlap_matrix for R");
  if(compute_overlap_matrix(*basisInfoStartingGuess, basisInfo, R) != 0)
  {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error in compute_overlap_matrix for matrix R");
      return -1;
  }


  ergo_real* S = ergo_new(n*n, ergo_real);
  if(compute_overlap_matrix(basisInfo, basisInfo, S) != 0)
  {
      do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error in compute_overlap_matrix for matrix S");
      return -1;
  }


  do_output(LOG_CAT_ERROR, LOG_AREA_MAIN, "error: get_inverse_of_posdef_symm_matrix not implemented.");
  return -1;


}
