flagbddnode( BddSystem, BddNode, Flag )

  bddsystem *BddSystem;
  bddnode   *BddNode;
  bddflag    Flag;
{
  setbddlocalsystem( BddSystem );

  BddFlagMask       = Flag;
  BddFlagNumberNode = 0;

  loc_flagbdd( BddNode );

  return( BddFlagNumberNode );
}
