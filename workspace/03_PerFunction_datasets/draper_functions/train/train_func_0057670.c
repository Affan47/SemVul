decodeNumber( Token &token )
{
   bool isDouble = false;
   for ( Location inspect = token.start_; inspect != token.end_; ++inspect )
   {
      isDouble = isDouble
                 ||  in( *inspect, '.', 'e', 'E', '+' )
                 ||  ( *inspect == '-'  &&  inspect != token.start_ );
   }
   if ( isDouble )
      return decodeDouble( token );
   Location current = token.start_;
   bool isNegative = *current == '-';
   if ( isNegative )
      ++current;
   Value::UInt threshold = (isNegative ? Value::UInt(-Value::minInt)
                                       : Value::maxUInt) / 10;
   Value::UInt value = 0;
   while ( current < token.end_ )
   {
      Char c = *current++;
      if ( c < '0'  ||  c > '9' )
         return addError( "'" + std::string( token.start_, token.end_ ) + "' is not a number.", token );
      if ( value >= threshold )
         return decodeDouble( token );
      value = value * 10 + Value::UInt(c - '0');
   }
   if ( isNegative )
      currentValue() = -Value::Int( value );
   else if ( value <= Value::UInt(Value::maxInt) )
      currentValue() = Value::Int( value );
   else
      currentValue() = value;
   return true;
}
