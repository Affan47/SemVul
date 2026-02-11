isIntegerNonBinary(int colIndex) const
{
  if ( isInteger(colIndex) && !isBinary(colIndex) )
    return true;
  else return false;
}
