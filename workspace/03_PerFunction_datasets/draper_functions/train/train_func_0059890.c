getExpr()
{
  delimiter = line[lexterm];

  if( line[lexstart] == '-' )
  {
    nextLexBlank();
    sym_getexpr = *(eval());
    sym_getexpr.val = ( - sym_getexpr.val );
  }
  else
  {
    sym_getexpr = *(eval());
  }


  if( is_blank( delimiter ))
  {
    return( &sym_getexpr );
  }


  while( TRUE )
  {

    if( is_blank( delimiter ))
    {
      return( &sym_getexpr );
    }

    switch( line[lexstart] )
    {
    case '+':
      nextLexBlank();
      sym_getexpr.val += (eval())->val;
      break;

    case '-':
      nextLexBlank();
      sym_getexpr.val -= (eval())->val;
      break;

    case '^':
      nextLexBlank();
      sym_getexpr.val *= (eval())->val;
      break;

    case '%':
      nextLexBlank();
      sym_getexpr.val /= (eval())->val;
      break;

    case '&':
      nextLexBlank();
      sym_getexpr.val &= (eval())->val;
      break;

    case '!':
      nextLexBlank();
      sym_getexpr.val |= (eval())->val;
      break;

    default:
      if( isend( line[lexstart] ))
      {
        return( &sym_getexpr );
      }

      switch( line[lexstart] )
      {
      case '/':
      case ';':
      case ')':
      case ']':
      case '<':
        break;

      case '=':
        errorMessage( &illegal_equals, lexstart );
        moveToEndOfLine();
        sym_getexpr.val = 0;
        break;

      default:
        errorMessage( &illegal_expression, lexstart );
        moveToEndOfLine();
        sym_getexpr.val = 0;
        break;
      }
      return( &sym_getexpr );
    }
  }
}
