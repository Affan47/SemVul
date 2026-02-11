save_symmetric_matrix(symmMatrix& A, const BasisInfoStruct & basisInfo,
                      const char *fileName,
		      std::vector<int> const & inversePermutationHML)
{
  int n = basisInfo.noOfBasisFuncs;
  do_output(LOG_CAT_INFO, LOG_AREA_SCF, "save_symmetric_matrix allocating full n*n matrix.");
  ergo_real* potentialMatrixFull = new ergo_real[n*n];
  normalMatrix* tmpMat;
  A.readFromFile();
  tmpMat = new normalMatrix(A);
  A.writeToFile();
  std::vector<ergo_real> fullTmp(n*n);
  tmpMat->fullMatrix(fullTmp,
		     inversePermutationHML,
		     inversePermutationHML);
  std::copy (fullTmp.begin(), fullTmp.end(), potentialMatrixFull);
  delete tmpMat;
  int ret = ddf_writeShellListAndDensityMatricesToFile(&basisInfo,
                                                       1,
                                                       &potentialMatrixFull,
                                                       fileName);
  delete [] potentialMatrixFull;
  return ret;
}
