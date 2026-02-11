createvexatomveclit( Literal, Width  )

  unsigned char Literal;
  short         Width;
{
  vexexpr *Node;
  char    *Name;
  char     Buffer[ 512 ];
  char     Cote;

  if ( Width > 1 ) Cote = '\"';
  else             Cote = '\'';

  Buffer[ 0         ] = Cote;
  Buffer[ Width + 1 ] = Cote;
  Buffer[ Width + 2 ] = '\0';

  memset( Buffer + 1, Literal, Width );

  Name = namealloc( Buffer );
  Node = allocvexnode();

  SetVexNodeAtom( Node );
  SetVexAtomValue( Node, Name );
  SetVexAtomLiteral( Node );

  Node->LEFT  = Width - 1;
  Node->RIGHT = 0;
  Node->WIDTH = Width;

  if ( Width > 1 ) SetVexAtomVector( Node );
  else             SetVexAtomBit( Node );

  return( Node );
}
