compute_operator_matrix_full(const BasisInfoStruct & basisInfoA,
			     const BasisInfoStruct & basisInfoB,
			     int pow_x,
			     int pow_y,
			     int pow_z,
			     ergo_real* result)
{
  int n_A = basisInfoA.noOfBasisFuncs;
  int n_B = basisInfoB.noOfBasisFuncs;
  std::vector<int> nvaluesList(n_A);
  std::vector< std::vector<int> > colindList(n_A);
  std::vector< std::vector<ergo_real> > valuesList(n_A);

  if(compute_operator_matrix_sparse(basisInfoA,
				    basisInfoB,
				    pow_x,
				    pow_y,
				    pow_z,
				    n_A,
				    n_B,
				    nvaluesList,
				    colindList,
				    valuesList) != 0)
    {
      do_output(LOG_CAT_ERROR, LOG_AREA_INTEGRALS, "error in compute_operator_matrix_sparse");
      return -1;
    }


  memset(result, 0, n_A*n_B*sizeof(ergo_real));
  for(int i = 0; i < n_A; i++)
    {
      int count = nvaluesList[i];
      const std::vector<int> & colind = colindList[i];
      const std::vector<ergo_real> & values = valuesList[i];
      for(int j = 0; j < count; j++)
	result[i*n_B+colind[j]] = values[j];
    }

  return 0;
}
