AllocateEdgeHashEntryPool()
{
  if ( freeEntryindex == 0 )
    {
    vtkTableBasedClipperEdgeHashEntry * newlist = new
    vtkTableBasedClipperEdgeHashEntry[ POOL_SIZE ];
    edgeHashEntrypool.push_back( newlist );

    for ( int i = 0; i < POOL_SIZE; i ++ )
      {
      freeEntrylist[i] = &( newlist[i] );
      }

    freeEntryindex = POOL_SIZE;
    }
}
