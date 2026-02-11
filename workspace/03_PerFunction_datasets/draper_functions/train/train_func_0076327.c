resetbddassoc( BddSystem, BddAssoc )

  bddsystem  *BddSystem;
  bddassoc   *BddAssoc;
{
  bddassocnode *BddAssocNode;
  bddvar        Variable;

  setbddlocalsystem( BddSystem );

  BddAssocNode = BddAssoc->ASSOC_NODE;

  if ( BddAssoc->FIRST != BDD_MAX_VAR )
  {
    for ( Variable  = BddAssoc->FIRST;
          Variable <= BddAssoc->LAST;
          Variable++ )
    {
      if ( BddAssocNode[ Variable ] != (bddnode *)0 )
      {
        decbddrefext( BddAssocNode[ Variable ] );
        BddAssocNode[ Variable ] = (bddnode *)0;
      }
    }

    BddAssoc->FIRST = BDD_MAX_VAR;
    BddAssoc->LAST  = BDD_MAX_VAR;

    if ( BddAssoc->CACHE )
    {
      BddLocalSystem->ASSOC_RESET = 1;
    }
  }
}
