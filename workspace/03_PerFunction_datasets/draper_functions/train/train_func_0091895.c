BoomCreateAuxInitComparatorAbl( Expr )

  ablexpr *Expr;
{
  ablexpr *ScanExpr;
  long     Oper;
  ablexpr *Operand1;
  ablexpr *Operand2;
  ablexpr *AuxExpr;
  char    *AuxName;

  if ( ! ABL_ATOM( Expr ) )
  {
    Oper = ABL_OPER( Expr );

    if ( ( Oper == ABL_XOR  ) ||
         ( Oper == ABL_NXOR ) )
    {
      ScanExpr = Expr;

      while ( ( ScanExpr = ABL_CDR( ScanExpr ) ) != (ablexpr *)0 )
      {
        if ( ! ABL_ATOM( ABL_CAR( ScanExpr ) ) ) break;
      }

      if ( ScanExpr == (ablexpr *)0 )
      {


        ScanExpr = Expr;
        Operand1 = (ablexpr *)0;

        while ( ( ScanExpr = ABL_CDR( ScanExpr ) ) != (ablexpr *)0 )
        {
          if ( Operand1 == (ablexpr *)0 )
          {
            Operand1 = ABL_CAR( ScanExpr );
            ABL_CAR_L( ScanExpr ) = (ablexpr *)0;

            continue;
          }

          Operand2 = ABL_CAR( ScanExpr );
          ABL_CAR_L( ScanExpr ) = (ablexpr *)0;

          AuxExpr = createablbinexpr( ABL_XOR, Operand1, Operand2 );
          AuxName = BoomGetNewAuxInitName();

          if ( IsBoomDebugLevel0() )
          {
            BoomPrintf( stdout, "Found a comparator, add aux init %s\n", AuxName );
          }

          BoomBehFigure->BEAUX = beh_addbeaux( BoomBehFigure->BEAUX, AuxName, AuxExpr, (void *)0 );
          BoomBehFigure->BERIN = beh_addberin( BoomBehFigure->BERIN, AuxName );
          BoomAddBehAuxInfo( BoomBehFigure->BEAUX );
          SetBoomBehAuxKeep( BoomBehFigure->BEAUX );

          Operand1 = createablatom( AuxName );
        }

        freeablexpr( Expr );

        Expr = Operand1;

        if ( Oper == ABL_NXOR ) Expr = optimablnotexpr( Expr );

        return( Expr );
      }
    }

    ScanExpr = Expr;

    while ( ( ScanExpr = ABL_CDR( ScanExpr ) ) != (ablexpr *)0 )
    {
      ABL_CAR_L( ScanExpr ) = BoomCreateAuxInitComparatorAbl( ABL_CAR( ScanExpr ) );
    }
  }

  return( Expr );
}
