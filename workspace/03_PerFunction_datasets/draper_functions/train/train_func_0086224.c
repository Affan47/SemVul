ScaleMatrix(Float scale, unsigned int matrixIndex)
{

  if( scale == 1.0 )
    {
    return;
    }

  unsigned int i;
  unsigned int j;
  for( i = 0; i < m_Order; i++ )
    {
    for( j = 0; j < m_Order; j++ )
      {
      this->SetMatrixValue(i, j, scale * GetMatrixValue(i, j, matrixIndex), matrixIndex);
      }
    }
}
