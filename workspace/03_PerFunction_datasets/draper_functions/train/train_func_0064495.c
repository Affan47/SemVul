XgraAddNode( Node, X, Y, Layer )

  autnode_list *Node;
  long          X;
  long          Y;
  short         Layer;
{
  xgraobj_list   *Circle;
  xgraobj_list   *Text;

  X *= XGRA_UNIT;
  Y *= XGRA_UNIT;

  Circle = XgraAddCircle( X, Y, XGRA_UNIT, Layer );
  Text   = XgraAddText( X, Y - ( ( 3 * XGRA_UNIT ) >> 1 ),
                        Node->NAME, Layer );

  Text->LINK   = Circle;
  Circle->LINK = Text;

  SetXgraNode( Circle );
  SetXgraNode( Text   );

  Circle->USER  = (void *)Node;
  Text->USER    = (void *)Node;
  Node->USER   = (void *)Circle;

  autend();
  return( Circle );
}
