restrictbddnode( BddSystem, BddNode, Variable, BddSubst )

  bddsystem *BddSystem;
  bddnode   *BddNode;
  bddvar     Variable;
  bddnode   *BddSubst;
{
  checkbddvar( BddSystem, Variable, 1 );

  if ( BddSubst->INDEX >= BDD_INDEX_MIN )
  {
    bdderror( BDD_BAD_INDEX_ERROR, BddSubst->INDEX );
  }

  BddLocalIndex    = BddLocalSystem->VAR_TO_INDEX[ Variable ];
  BddLocalVariable = Variable;
  BddLocalNode     = BddSubst;

  BddNode = loc_restrictbdd( BddNode );

  checkbddmaxnode( (bddsystem *)0, 1 );

  return( BddNode );
}
