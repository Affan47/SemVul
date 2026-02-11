getnum( msg, num, format )
char *msg;
void *num;
char *format;
{
char s[40];

printf( "%s (", msg );
if( format == strfmt )
	printf( format, (char *) num );
else if( format == dblfmt )
	printf( format, *(double *)num );
else if( format == intfmt )
	printf( format, *(int *)num );
else if( format == lngfmt )
	printf( format, *(long *)num );
else
	printf( "Illegal input format\n"  );
printf( ") ? ");
{
  char *str;
  if (fgets(s,40,stdin) == NULL)
    exit(0);
  if ((str = strchr(s, '\n')))
    *str=0;
}
if( s[0] != '\0' )
	sscanf( s, format, num );
return(0);
}
