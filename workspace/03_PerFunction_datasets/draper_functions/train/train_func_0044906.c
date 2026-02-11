InsertNodeSorted( TLWNode *n ) {
  TLWNode *walk = static_cast<TLWNode *>( Tail() );

  while ( walk && (strcmp( n->Name(), walk->Name()) < 0) )
    walk = static_cast<TLWNode *>( walk->Prev() );

  InsertNode( n, walk );
}
