addbddnode( BddSystem, Index, High, Low  )

  bddsystem *BddSystem;
  bddindex   Index;
  bddnode   *High;
  bddnode   *Low;
{
  bddblock *BddBlock;
  bddnode  *BddNode;
  bddnode  *NewBddNode;

  setbddlocalsystem( BddSystem );

  if ( Index >= BddLocalSystem->NUMBER_INDEX )
  {
    bdderror( BDD_BAD_INDEX_ERROR, Index );
  }

  if ( ( ! IsBddSystemSwapVar( BddLocalSystem )                         ) &&
       ( IsBddSystemExplosionOn( BddLocalSystem )                       ) &&
       ( BddLocalSystem->EXPLOSION_LIMIT <= BddLocalSystem->NUMBER_NODE ) )
  {
    if ( ! IsBddSystemExplosion( BddLocalSystem ) )
    {
      BddLocalSystem->HASH_OPER->TABLE_FREEZE;

      if ( BddLocalSystem->EXPLOSION_FUNC != NULL )
      {
        BddLocalSystem->EXPLOSION_FUNC( BddLocalSystem );
      }
      else
      {
        if ( ! IsBddSystemNoWarning( BddLocalSystem ) )
        {
          bddwarning( BDD_DYNAMIC_EXPLOSION_WARNING,
                      BddLocalSystem->NUMBER_NODE, BddLocalSystem->EXPLOSION_LIMIT );
        }
      }

      SetBddSystemExplosion( BddLocalSystem );
    }

    return( BddLocalSystem->ZERO );
  }

  if ( High == (bddnode *)0 ) High = &BddTerminalHighNode;
  if ( Low  == (bddnode *)0 ) Low  = &BddTerminalLowNode;

  if ( High == Low )
  {
    return( incbddrefext( High ) );
  }

  BddBlock = BddLocalSystem->BLOCK;

  if ( BddLocalSystem->NODE_FREE == (bddnode *)0 )
  {
    if ( ( BddBlock == (bddblock *)0 ) ||
         ( BddBlock->NODE_FREE == 0  ) )
    {
      BddBlock = addbddblock( (bddsystem *)0 );
    }

    BddBlock->NODE_FREE--;
    BddNode = &BddBlock->NODE[ BddBlock->NODE_FREE ];
  }
  else
  {
    BddNode = BddLocalSystem->NODE_FREE;
    BddLocalSystem->NODE_FREE = BddNode->HIGH;

    BddLocalSystem->NUMBER_FREE--;
  }

  BddNode->HIGH  = High;
  BddNode->LOW   = Low;
  BddNode->INDEX = Index;

  NewBddNode = addbddhnode( BddLocalSystem->INDEX_NODE[ Index ], BddNode );

  if ( NewBddNode == BddNode )
  {
    incbddrefint( High );
    incbddrefint( Low  );
    BddNode->MARK = 0;
    BddNode->FLAG = 0;

    BddLocalSystem->NUMBER_NODE++;

    if ( BddLocalSystem->NUMBER_NODE > BddLocalSystem->TOP_NODE )
    {
      BddLocalSystem->TOP_NODE = BddLocalSystem->NUMBER_NODE;
    }
  }
  else
  {
    BddNode->LOW   = (bddnode *)0;
    BddNode->INDEX = 0;

    BddNode->HIGH  = BddLocalSystem->NODE_FREE;
    BddLocalSystem->NODE_FREE = BddNode;

    BddLocalSystem->NUMBER_FREE++;
  }

  return( incbddrefext( NewBddNode ) );
}
