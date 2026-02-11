ScaleMatrix(Float scale, unsigned int matrixIndex)
{
  ( *( ( *m_Matrices )[matrixIndex] ) ) = ( *( ( *m_Matrices )[matrixIndex] ) ) * scale;
}
