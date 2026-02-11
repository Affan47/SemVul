DumpSetWdForC( void )
#else
DumpSetWdForC( )
#endif
{
	int i,c=1;

	if ( setwd==NULL ) return;
	fprintf(DefFile, "extern SetWordType setwd%d[];\n", wordnum);
	fprintf(ErrFile,
			"SetWordType setwd%d[%d] = {", wordnum, TokenNum-1);
	for (i=0; i<TokenNum-1; i++)
	{
		DAWDLE;
		if ( i!=0 ) fprintf(ErrFile, ",");
		if ( c == 8 ) {fprintf(ErrFile, "\n\t"); c=1;} else c++;
		fprintf(ErrFile, "0x%x", setwd[i]);
	}
	fprintf(ErrFile, "};\n");
}
