EvaluatePDF(double x, const ParametersType & p) const
{
  if ( p.GetSize() != 1 )
    {
    itkGenericExceptionMacro(
      "Invalid number of parameters to describe distribution. Expected 1 parameter, but got "
      << p.size()
      << " parameters.");
    }
  return TDistribution::PDF( x, static_cast< SizeValueType >( p[0] ) );
}
