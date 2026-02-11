ShapeFunctionDerivatives(const VectorType &, MatrixType & shapeD) const
{

  shapeD.set_size(3, 4);
  shapeD.fill(0.0);

  for( int j = 0; j < 3; j++ )
    {
    shapeD[j][0] = -1;
    }

  for( int j = 1; j < 4; j++ )
    {
    shapeD[j - 1][j] = 1;
    }
}
