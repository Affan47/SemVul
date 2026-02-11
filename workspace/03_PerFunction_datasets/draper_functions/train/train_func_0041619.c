createvexatomlit( Name )

  char *Name;
{
  vexexpr  *Node;
  short     Width;

  Name = namealloc( Name );
  Node = allocvexnode();

  SetVexNodeAtom( Node );
  SetVexAtomValue( Node, Name );
  SetVexAtomLiteral( Node );

  Width = strlen( Name ) - 2;

  Node->LEFT  = Width - 1;
  Node->RIGHT = 0;
  Node->WIDTH = Width;

  if ( Width > 1 ) SetVexAtomVector( Node );
  else             SetVexAtomBit( Node );

  return( Node );
}
