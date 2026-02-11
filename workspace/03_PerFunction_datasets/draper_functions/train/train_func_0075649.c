multiplyMatrices (const Matrixd& m1, const Matrixd& m2)
{
  int rows1 = m1.size();
  int cols1 = m1[0].size();

  int rows2 = m2.size();
  int cols2 = m2[0].size();


  if ( rows2 != cols1)
  {
    return (Matrixd());
  }


  Matrixd outputMatrix;
  int i;
  for ( i = 0; i < rows1; i++)
  {
    outputMatrix.push_back (vector<double> (cols2,0));
  }

  int j,k;

  for ( i = 0; i < rows1; i++)
  {
    for ( j = 0; j < cols2; j++)
    {
      for (k = 0; k < rows2; k++)
      {
        outputMatrix[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }

  return outputMatrix;
}
