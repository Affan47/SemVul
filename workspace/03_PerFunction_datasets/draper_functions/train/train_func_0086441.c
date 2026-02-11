loc_getvexallnameatom( Expr )

  vexexpr *Expr;
{
  chain_list  *ScanName;
  char        *AtomName;

  if ( ! IsVexAtomLiteral( Expr ) )
  {
    AtomName = GetVexAtomValue( Expr );

    for ( ScanName  = VexGetHeadChain;
          ScanName != (chain_list *)0;
          ScanName  = ScanName->NEXT )
    {
      if ( ScanName->DATA == AtomName ) return;
    }

    VexGetHeadChain = addchain( VexGetHeadChain, AtomName );
  }
}
