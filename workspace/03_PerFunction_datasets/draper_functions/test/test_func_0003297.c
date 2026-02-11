ConvertExternalToInternalGradient(const DerivativeType   & input,
                                    InternalDerivativeType & output) const
{
  const unsigned int size = input.size();

  output = InternalDerivativeType(size);
  const ScalesType & invScales = this->GetInverseScales();
  for ( unsigned int i = 0; i < size; i++ )
    {
    if ( !m_NegateCostFunction )
      {
      output[i] = input[i];
      }
    else
      {
      output[i] = -input[i];
      }

    if ( m_ScalesInitialized )
      {
      output[i] *= invScales[i];
      }
    }
}
