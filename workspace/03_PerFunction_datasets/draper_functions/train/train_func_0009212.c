addbddnodeassoc( BddSystem, BddAssoc, Variable, BddNode )

  bddsystem  *BddSystem;
  bddassoc   *BddAssoc;
  bddvar      Variable;
  bddnode    *BddNode;
{
  bddassocnode *BddAssocNode;

  checkbddvar( BddSystem, Variable, 1 );

  BddAssocNode = BddAssoc->ASSOC_NODE;

  if ( BddAssocNode[ Variable ] != (bddnode *)0 )
  {
    decbddrefext( BddAssocNode[ Variable ] );
  }
  else
  {
    if ( ( BddAssoc->FIRST == BDD_MAX_VAR    ) ||
         ( Variable        < BddAssoc->FIRST ) ) BddAssoc->FIRST = Variable;

    if ( ( BddAssoc->LAST  == BDD_MAX_VAR    ) ||
         ( Variable        > BddAssoc->LAST  ) ) BddAssoc->LAST  = Variable;
  }

  BddAssocNode[ Variable ] = incbddrefext( BddNode );

  if ( BddAssoc->CACHE )
  {
    BddLocalSystem->ASSOC_RESET = 1;
  }

  return( BddAssoc );
}
