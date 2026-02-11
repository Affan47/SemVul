rdsalloc( Size, Heap )

      unsigned long Size;
      char          Heap;
{
  long          Counter;
  unsigned long Index;
  char         *Pointer;
  char        **Prev;
  char         *Scan;

  if ( InitRdsHeapHeadArray == 1 )
  {
    InitRdsHeapHeadArray = 0;

    for ( Counter = 0; Counter < 256 ; Counter++ )
    {
      RdsHeapHeadArray[ Counter ] = (char *)NULL;
    }
  }

  Index = ( Size + 3 ) >> 2;

  if ( ( Heap    == RDS_ALLOC_BLOCK ) ||
       ( Index   >  255             ) )
  {
    if ( !( Pointer = malloc( Size ) ) )
    {
      rdserror( RDS_ALLOC_ERROR, (char *)NULL );
    }

    bzero( Pointer, Size );

    return( Pointer );
  }

  Size = Index << 2;

  if ( RdsHeapHeadArray[ Index ] == (char *)NULL )
  {
    if ( !( Pointer = malloc( Size << RDS_ALLOC_SHIFT ) ) )
    {
      rdserror( RDS_ALLOC_ERROR, (char *)NULL );
    }

    Scan = (char *)(Pointer + Size);

    Prev = &RdsHeapHeadArray[ Index ];

    for ( Counter = 1; Counter < RDS_ALLOC_SIZE; Counter++ )
    {
      *Prev = Scan; Prev = (char **)Scan; Scan = (char *)(Scan + Size);
    }

    *Prev = (char *)NULL;

    RdsHeapHeadArray[ Index ] = (char *)(Pointer + Size);

    bzero( Pointer, Size );

    return( Pointer );
  }

  Pointer = RdsHeapHeadArray[ Index ];

  RdsHeapHeadArray[ Index ] = *((char **)RdsHeapHeadArray[ Index ]);

  bzero( Pointer, Size );

  return( Pointer );
}
