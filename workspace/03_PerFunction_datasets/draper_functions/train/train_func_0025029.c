implybddnode( BddSystem, BddNode1, BddNode2 )

  bddsystem *BddSystem;
  bddnode   *BddNode1;
  bddnode   *BddNode2;
{
  setbddlocalsystem( BddSystem );

  BddNode2 = decbddrefext( loc_applybddnot( BddNode2 ) );
  BddNode1 = loc_intersectbdd( BddNode1, BddNode2 );

  checkbddmaxnode( (bddsystem *)0, 1 );

  return( BddNode1 );
}
