ModuloValue(INT input, INT bufferlength)
{
  if ( input > (bufferlength - 1) ) {
    return (input - bufferlength);
  }
  if ( input < 0 ) {
    return (input + bufferlength);
  }
  return input;
}
