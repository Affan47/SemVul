fincat( name, n, str1, str2 )
char *name;
int n;
char *str1, *str2;
{
int i;
FILE *f, *fopen();

f = fopen( name, "r" );
if( f == 0 )
	{
	printf( "Can't find file %s\n", name );
	return(0);
	}

getnum( "Line number", &linenum, intfmt );
if( linenum <= 0 )
	goto failure;

for( i=0; i<linenum; i++ )
	{

	fgets( str1, 126, f );
	if( *str1 == '-' )
		goto endf;
	if( n > 1 )
		{
		fgets( str2, 126, f );
		if( *str2 == '-' )
			goto endf;
		}
	}
fclose(f);
return( f );


endf:
printf( "End of file reached.\n" );
failure:
fclose(f);
return(0);
}
