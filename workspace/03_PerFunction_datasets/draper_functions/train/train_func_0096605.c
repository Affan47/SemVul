InitializeMatrix(unsigned int matrixIndex)
{


  if( m_Matrices == ITK_NULLPTR )
    {
    m_Matrices = new MatrixHolder(m_NumberOfMatrices);
    if( m_Matrices == ITK_NULLPTR )
      {
      itkGenericExceptionMacro(<< "LinearSystemWrapperVNL::InitializeMatrix(): m_Matrices allocation failed.");
      }
    }


  delete ( *m_Matrices )[matrixIndex];

  ( *m_Matrices )[matrixIndex] = new MatrixRepresentation( this->GetSystemOrder(), this->GetSystemOrder() );
  if( ( *m_Matrices )[matrixIndex] == ITK_NULLPTR )
    {
    itkGenericExceptionMacro(
      << "LinearSystemWrapperVNL::InitializeMatrix(): allocation of (*m_Matrices)[" << matrixIndex << "] failed.");
    }
}
