destroyautgraph( Graph )

  autgraph *Graph;
{
  autnode_list *ScanNode;
  autnode_list *DelNode;
  autarc_list  *ScanArc;
  autarc_list  *DelArc;

  ScanNode = Graph->NODE;

  while( ScanNode != (autnode_list *)0 )
  {
    DelNode  = ScanNode;
    ScanNode = ScanNode->NEXT;

    freechain( DelNode->ARC_FROM );
    freechain( DelNode->ARC_TO   );

    autfreeheap( DelNode, sizeof( autnode_list ) );
  }

  ScanArc = Graph->ARC;

  while( ScanArc != (autarc_list *)0 )
  {
    DelArc  = ScanArc;
    ScanArc = ScanArc->NEXT;

    autfreeheap( DelArc, sizeof( autarc_list ) );
  }

  destroyauthtable( Graph->HASH_NODE );
  destroyauth2table( Graph->HASH_ARC );

  autfreeheap( Graph, sizeof( autgraph ) );
}
