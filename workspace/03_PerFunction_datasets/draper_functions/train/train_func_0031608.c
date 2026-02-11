getDetailledName() const
{
   if ( turn >= 0 ) {
      ASCString s;
      s.format( "turn %d , move %d passed ", turn, move );
      return s;
   } else
      return getTypeName();
}
