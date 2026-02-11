destroybddsystem( BddSystem )

  bddsystem *BddSystem;
{
  bddindexnode *IndexNode;
  bddindex      NumberIndex;
  bddindex      Index;

  setbddlocalsystem( BddSystem );

  destroybddblock( (bddsystem *)0 );
  destroybddassoc( (bddsystem *)0 );
  destroybdduserfunc( (bddsystem *)0 );

  destroybddhopertable( BddLocalSystem->HASH_OPER );

  NumberIndex = BddLocalSystem->NUMBER_INDEX;
  IndexNode   = BddLocalSystem->INDEX_NODE;

  destroybddhnodetable( IndexNode[ BDD_INDEX_ZERO ] );

  for ( Index = BDD_INDEX_MIN; Index < NumberIndex; Index++ )
  {
    destroybddhnodetable( IndexNode[ Index ] );
  }

  freebddvar( BddLocalSystem->INDEX_TO_VAR );
  freebddindex( BddLocalSystem->VAR_TO_INDEX );

  freebddindexnode( BddLocalSystem->INDEX_NODE );
  freebddvarnode( BddLocalSystem->VAR_NODE );

  freebddsystem( BddLocalSystem );

  BddLocalSystem = (bddsystem *)0;
}
