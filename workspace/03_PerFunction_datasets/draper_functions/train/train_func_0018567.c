UpperToLowerOrder(int dim)
{
  int **mat = new int *[dim];

  for ( int i = 0; i < dim; i++ )
    {
    mat[i] = new int[dim];
    }

  int index(0);
  for ( int i = 0; i < dim; i++ )
    {
    for ( int j = i; j < dim; j++ )
      {
      mat[i][j] = index;
      mat[j][i] = index;
      index++;
      }
    }
  int *rval = new int[index + 1];
  int  index2(0);
  for ( int i = 0; i < dim; i++ )
    {
    for ( int j = 0; j <= i; j++, index2++ )
      {
      rval[index2] = mat[i][j];
      }
    }
  rval[index2] = -1;
  for ( int i = 0; i < dim; i++ )
    {
    delete[] mat[i];
    }
  delete[] mat;
  return rval;
}
