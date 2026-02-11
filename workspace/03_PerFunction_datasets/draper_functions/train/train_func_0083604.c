add_disturbance_to_matrix(int n,
			  symmMatrix & A,
			  ergo_real disturbance,
			  int specificElementCount,
			  const int* elementIndexVector,
			  std::vector<int> const & permutationHML)
{

  std::vector<ergo_real> diagonalValues(n);
  std::vector<int> rowind(n);
  std::vector<int> colind(n);
  for(int i = 0; i < n; i++)
    diagonalValues[i] = 0;
  if(specificElementCount == 0)
    {

      for(int i = 0; i < n; i++)
	{
	  double randomNumber = (double)rand() / RAND_MAX;

	  randomNumber *= 2;

	  randomNumber -= 1;

	  diagonalValues[i] = randomNumber * disturbance;
	}
    }
  else
    {

      for(int i = 0; i < specificElementCount; i++)
	{
	  int idx = elementIndexVector[i];
	  if(idx >= 0 && idx < n)
	    diagonalValues[idx] = disturbance;
	}
    }
  for(int i = 0; i < n; i++)
    {
      rowind[i] = i;
      colind[i] = i;
    }
  symmMatrix B(A);
  B.clear();
  B.assign_from_sparse(rowind,
		       colind,
		       diagonalValues,
		       permutationHML,
		       permutationHML);
  A += (ergo_real)1.0 * B;

  return 0;
}
