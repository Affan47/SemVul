VasyVerilogBinary ( Range, Value )

  long Range;
  long Value;
{
  static char Buffer[ 256 ];
  int Index;
  int Shift;

  sprintf( Buffer, "%ld'b", Range );


  Shift = strlen( Buffer );

  for ( Index = Range - 1;
        Index >= 0;
        Index -- )
  {
    Buffer[ Shift + Range - 1 - Index ] = (( Value << Index ) & 1) + '0' ;
  }

  Buffer[ Shift + Range ] = (char)0;

  return Buffer;
}
