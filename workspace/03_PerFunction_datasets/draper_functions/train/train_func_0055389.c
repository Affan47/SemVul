GetChar ( void )
{
  Char c;


  GET_CHAR();


  if ( *In == '\\' ) {
    GET_CHAR();
    if ( *In == 'n'  )       Value[0] = '\n';
    else if ( *In == 't'  )  Value[0] = '\t';
    else if ( *In == 'r'  )  Value[0] = '\r';
    else if ( *In == 'b'  )  Value[0] = '\b';
    else if ( *In == '>'  )  Value[0] = '\01';
    else if ( *In == '<'  )  Value[0] = '\02';
    else if ( *In == 'c'  )  Value[0] = '\03';
    else if ( *In >= '0' && *In <= '7' ) {

      c = 64 * (*In - '0');
      GET_CHAR();
      if ( *In < '0' || *In > '7' )
        SyntaxError("expecting octal digit in character constant");
      c = c + 8 * (*In - '0');
      GET_CHAR();
      if ( *In < '0' || *In > '7' )
        SyntaxError("expecting 3 octal digits in character constant");
      c = c + (*In - '0');
      Value[0] = c;
    }
    else                     Value[0] = *In;
  }


  else {
    Value[0] = *In;
  }


  GET_CHAR();


  if ( *In != '\'' )
    SyntaxError("missing single quote in character constant");


  Symbol = S_CHAR;
  if ( *In == '\'' )  GET_CHAR();

}
