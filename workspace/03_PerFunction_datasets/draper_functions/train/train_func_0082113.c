printPermanentSymbolTable()
{
  int     ix;
  FILE   *permfile;
  char  *s_type;

  if(( permfile = fopen( permpathname, "w" )) == NULL )
  {
    exit( 2 );
  }

  fprintf( permfile, "/ PERMANENT SYMBOL TABLE\n/\n" );
  fprintf( permfile, "        EXPUNGE\n/\n" );

  s_type = "FIXMRI";
  for( ix = 0; ix < symbol_top; ix++ )
  {
    if( M_MRI( symtab[ix].type ))
    {
      fprintf( permfile, "%-7s %s=%4.4o\n",
                                    s_type, symtab[ix].name, symtab[ix].val );
    }
  }

  s_type = " ";
  for( ix = 0; ix < symbol_top; ix++ )
  {
    if( M_FIXED( symtab[ix].type ))
    {
      if( !M_MRI( symtab[ix].type ) && !M_PSEUDO( symtab[ix].type ))
      {
        fprintf( permfile, "%-7s %s=%4.4o\n",
                                    s_type, symtab[ix].name, symtab[ix].val );
      }
    }
  }
  fprintf( permfile, "/\n        FIXTAB\n" );
  fclose( permfile );
}
