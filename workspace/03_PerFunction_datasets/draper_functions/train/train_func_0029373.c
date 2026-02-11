viewautgraph( Graph, FuncViewNode, FuncViewArc )

  autgraph  *Graph;
  void     (*FuncViewNode)();
  void     (*FuncViewArc)();
{
  autnode_list *ScanNode;
  chain_list   *ScanChain;
  autarc_list  *ScanArc;

  for ( ScanNode  = Graph->NODE;
        ScanNode != (autnode_list *)0;
        ScanNode  = ScanNode->NEXT )
  {
    if ( FuncViewNode )
    {
      FuncViewNode( Graph, ScanNode );
    }
    else
    {
      fprintf( stdout, "NODE: %s\n", ScanNode->NAME );
    }

    fprintf( stdout, "> ARC_FROM:\n" );

    for ( ScanChain  = ScanNode->ARC_FROM;
          ScanChain != (chain_list *)0;
          ScanChain  = ScanChain->NEXT )
    {
      ScanArc = (autarc_list *)ScanChain->DATA;

      if ( FuncViewArc )
      {
        FuncViewArc( Graph, ScanArc );
      }
      else
      {
        fprintf( stdout, "> TO %s\n", ScanArc->NODE_TO->NAME );
      }
    }

    fprintf( stdout, "> ARC_TO:\n" );

    for ( ScanChain  = ScanNode->ARC_TO;
          ScanChain != (chain_list *)0;
          ScanChain  = ScanChain->NEXT )
    {
      ScanArc = (autarc_list *)ScanChain->DATA;

      if ( FuncViewArc )
      {
        FuncViewArc( Graph, ScanArc );
      }
      else
      {
        fprintf( stdout, "> FROM %s\n", ScanArc->NODE_FROM->NAME );
      }
    }
  }
}
