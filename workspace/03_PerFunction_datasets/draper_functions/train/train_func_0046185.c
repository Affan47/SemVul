InitializeVector(unsigned int vectorIndex)
{

  if( m_Vectors == 0 )
    {
    m_Vectors = new std::vector<vnl_vector<Float> *>(m_NumberOfVectors);
    if( m_Vectors == NULL )
      {
      itkGenericExceptionMacro(<< "InitializeVector(): m_Vectors memory allocation failed.");
      }
    }


  if( ( *m_Vectors )[vectorIndex] != 0 )
    {
    delete ( *m_Vectors )[vectorIndex];
    }

  ( *m_Vectors )[vectorIndex] = new vnl_vector<Float>( this->GetSystemOrder() );
  if( ( *m_Vectors )[vectorIndex] == NULL )
    {
    itkGenericExceptionMacro(<< "InitializeVector(): allocation of (*m_Vectors)[" << vectorIndex << "] failed.");
    }
  ( *m_Vectors )[vectorIndex]->fill(0.0);

  return;
}
