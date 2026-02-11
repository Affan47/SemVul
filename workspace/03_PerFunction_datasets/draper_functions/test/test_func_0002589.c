applybddnodeite( BddSystem, BddIf, BddThen, BddElse )

  bddsystem *BddSystem;
  bddnode   *BddIf;
  bddnode   *BddThen;
  bddnode   *BddElse;
{
  setbddlocalsystem( BddSystem );

  BddThen = loc_applybdd( ABL_AND, BddIf, BddThen );
  checkbddmaxnode( (bddsystem *)0, 1 );
  BddIf   = loc_applybddnot( BddIf );
  checkbddmaxnode( (bddsystem *)0, 1 );
  BddElse = loc_applybdd( ABL_AND,
                          decbddrefext( BddIf   ),
                          decbddrefext( BddElse ) );
  checkbddmaxnode( (bddsystem *)0, 1 );
  BddIf   = loc_applybdd( ABL_OR ,
                          decbddrefext( BddThen ),
                          decbddrefext( BddElse ) );
  checkbddmaxnode( (bddsystem *)0, 1 );

  return( BddIf );
}
