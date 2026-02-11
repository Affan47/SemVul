InitializeMatrix(unsigned int matrixIndex)
{

  if( m_Matrices == ITK_NULLPTR )
    {
    m_Matrices = new MatrixHolder(m_NumberOfMatrices);
    }


  delete ( *m_Matrices )[matrixIndex];

  ( *m_Matrices )[matrixIndex] = new MatrixRepresentation( this->GetSystemOrder(), this->GetSystemOrder() );
  ( *m_Matrices )[matrixIndex]->fill(0.0);
}
