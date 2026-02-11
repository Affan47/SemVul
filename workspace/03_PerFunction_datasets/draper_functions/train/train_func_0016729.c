resizebddhnodetable( HashTable )

  bddhnodetable *HashTable;
{
  bddhnode *NewTable;
  bddhnode *Table;
  long      NewLength;
  long      Length;
  long      NumberNode;

  Length     = HashTable->TABLE_SIZE;
  NumberNode = HashTable->NUMBER_NODE;

  if ( NumberNode >= ( Length * BDD_HNODE_MIN_FILL_FACTOR ) / 100 )
  {
    return;
  }

  Table      = HashTable->TABLE;
  NewLength  = (*funcbddhnodesize)( NumberNode * BDD_HNODE_RESIZE_FACTOR / 100 );
  NewTable   = allocbddhnode( NewLength );

  HashTable->TABLE          = NewTable;
  HashTable->TABLE_SIZE     = NewLength;
  HashTable->NUMBER_NODE    = 0;
  HashTable->NUMBER_RESIZE += 1;

  while ( Length > 0 )
  {
    Length = Length - 1;

    if ( ( Table[ Length ] != BDD_HASH_NODE_EMPTY   ) &&
         ( Table[ Length ] != BDD_HASH_NODE_DELETED ) )
    {
      addbddhnode( HashTable, Table[ Length ] );
    }
  }

  freebddhnode( Table );
}
