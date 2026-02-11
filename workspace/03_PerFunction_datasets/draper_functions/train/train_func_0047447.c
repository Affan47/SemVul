luaQuote( const ASCString& text )
{
   int count = 0;
   while( text.find_first_of( getLuaQuote( true,  count )) != ASCString::npos ||
          text.find_first_of( getLuaQuote( false, count )) != ASCString::npos )
      ++count;

   return getLuaQuote( true, count) + text + getLuaQuote( false, count );
}
