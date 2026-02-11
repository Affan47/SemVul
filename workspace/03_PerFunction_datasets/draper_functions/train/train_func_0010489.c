createvexoper( Oper, Width )

  long  Oper;
  short Width;
{
  vexexpr *Node;

  if ( ( Oper < 0                 ) ||
       ( Oper >= VEX_MAX_OPERATOR ) )
  {
    vexerror( VEX_OPERATOR_ERROR, Oper );
  }

  Node = allocvexnode();

  if ( Width <= 0 )
  {
    Width = 1;
    SetVexNodeVarWidth( Node );
  }

  Node->WIDTH = Width;
  Node->LEFT  = Width - 1;

  SetVexNodeOper( Node );
  SetVexOperValue( Node, Oper );

  return( Node );
}
