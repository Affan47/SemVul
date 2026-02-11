main( argc, argv )

   int   argc;
   char *argv[];
{
  rdsfig_list *Figure;

  Banner();

  mbkenv();
  rdsenv();
  loadrdsparam();

  if ( argc < 4 ) Usage();

  if ( ! strcmp( "-r", argv[1] ) )
  {
     Figure = getrdsfig( argv[2], 'A', 0 );

     fprintf( stdout, "\n   --> Flatten figure %s to the catalog\n",
              Figure->NAME );

     rflattenrdsfig( Figure, RDS_YES, RDS_YES );
  }
  else
  if ( ! strcmp( "-t", argv[1] ) )
  {
     Figure = getrdsfig( argv[2], 'A', 0 );

     fprintf( stdout, "\n   --> Flatten figure %s to the transistor\n",
              Figure->NAME );

     rflattenrdsfig( Figure, RDS_YES, RDS_NO );
  }
  else
  {
    Figure = getrdsfig( argv[1], 'A', 0 );

    fprintf( stdout, "\n   --> Flatten the instance %s in the figure %s\n",
             argv[2], Figure->NAME );

    flattenrdsfig( Figure, argv[2], RDS_YES );
  }

  Figure->NAME = namealloc( argv[3] );

  fprintf( stdout, "   --> Saving figure %s \n\n", Figure->NAME );

  saverdsfig( Figure );

  return( 0 );
}
