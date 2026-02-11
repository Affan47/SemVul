get_maximum_norm(int m, int n, const ergo_real* A)
{
  int i, j;
  ergo_real largestSum = 0;
  for(i = 0; i < m; i++)
    {
      ergo_real sum = 0;
      for(j = 0; j < n; j++)
	sum += std::fabs(A[j*m+i]);
      if(sum > largestSum)
	largestSum = sum;
    }

  ergo_real maximumNorm = largestSum;


  return maximumNorm;
}
