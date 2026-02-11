IsCompatible(const TransferSyntax & ts ) const
{
  if( ts == TransferSyntax::JPEGBaselineProcess1 && BitsAllocated != 8 ) return false;

  return true;
}
