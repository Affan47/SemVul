ParseAtomExpr( int level )
  {
    register AtomExpr *expr1;
    register AtomExpr *expr2;
    register char *prev;

    switch( level )
      {
      case(0):
        if( !(expr1=ParseAtomExpr(1)) )
          return (AtomExpr*)0;

        while( *LexPtr == ';' )
          {
            LexPtr++;
            if( !(expr2=ParseAtomExpr(1)) )
              {
                FreeAtomExpr(expr1);
                return (AtomExpr*)0;
              }
            expr1 = BuildAtomBin(AE_ANDLO,expr1,expr2);
          }
        return expr1;

      case(1):
        if( !(expr1=ParseAtomExpr(2)) )
          return (AtomExpr*)0;

        while( *LexPtr == ',' )
          {
            LexPtr++;
            if( !(expr2=ParseAtomExpr(2)) )
              {
                FreeAtomExpr(expr1);
                return( (AtomExpr*)0 );
              }
            expr1 = BuildAtomBin(AE_OR,expr1,expr2);
          }
        return( expr1 );

      case(2):
        if( !(expr1=ParseAtomExpr(3)) )
          return( (AtomExpr*)0 );

        while( (*LexPtr!=']') && (*LexPtr!=';') &&
               (*LexPtr!=',') && *LexPtr )
          {
            if( *LexPtr=='&' )
              LexPtr++;
            prev = LexPtr;
            if( !(expr2=ParseAtomExpr(3)) )
              {
                if( prev != LexPtr )
                  {
                    FreeAtomExpr(expr1);
                    return( (AtomExpr*)0 );
                  }
                else
                  return( expr1 );
              }
            expr1 = BuildAtomBin(AE_ANDHI,expr1,expr2);
          }
        return( expr1 );

      case(3):
        if( *LexPtr == '!' )
          {
            LexPtr++;
            if( !(expr1=ParseAtomExpr(3)) )
              return( (AtomExpr*)0 );
            return( BuildAtomNot(expr1) );
          }
        return( ParseComplexAtomPrimitive() );
      }
    return (AtomExpr*)0;
  }
