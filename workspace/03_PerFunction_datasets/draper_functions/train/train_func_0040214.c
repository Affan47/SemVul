B2fTreatRegister( BehFigure )

  befig_list  *BehFigure;
{
  bddcircuit  *BddCircuit;
  bereg_list  *ScanReg;
  binode_list *BiNode;
  bddnode     *BddNode;
  chain_list  *Expr;
  chain_list  *Support;
  char        *RegName;
  long         Index;

  B2fNumberRegister = 0;
  B2fRegisterName   = (char *)0;
  BddCircuit        = BehFigure->CIRCUI;
  BddNode           = (bddnode    *)0;
  Expr              = (chain_list *)0;


  for ( ScanReg  = BehFigure->BEREG;
        ScanReg != (bereg_list *)0;
        ScanReg  = ScanReg->NEXT )
  {
    RegName = vhdlablvector( ScanReg->NAME, &Index );

    if ( RegName == (char *)0 )
    {
      B2fError( B2F_REGISTER_NOT_A_VECTOR, ScanReg->NAME );
    }

    BiNode = ScanReg->BINODE;

    if ( BddNode == (bddnode *)0 )
    {
      Expr    = ScanReg->BIABL->CNDABL;
      BddNode = BiNode->CNDNODE;

      B2fRegisterName = RegName;
    }
    else
    if ( BiNode->CNDNODE != BddNode )
    {
      B2fError( B2F_BAD_CONDITION_REGISTER, ScanReg->NAME );
    }
    else
    if ( B2fRegisterName != RegName )
    {
      B2fError( B2F_BAD_REGISTER_NAME, B2fRegisterName );
    }

    B2fNumberRegister = B2fNumberRegister + 1;
  }

  if ( BddNode != (bddnode *)0 )
  {
    B2fFsmFigure->CLOCK_ABL = dupablexpr( Expr );
    Support = getablexprsupport( Expr, ABL_SUPPORT_CHAIN );

    if ( ( Support       == (chain_list *)0 ) ||
         ( Support->NEXT != (chain_list *)0 ) )
    {
      B2fError( B2F_BAD_CONDITION_REGISTER, RegName );
    }

    B2fFsmFigure->CLOCK = (char *)Support->DATA;
  }
  else
  {
    B2fError( B2F_NO_REGISTER, BehFigure->NAME );
  }

  B2fRegisterName   = RegName;

# ifdef DEBUG
  fprintf( stdout, "Found %ld registers\n", NumberReg );
# endif
}
