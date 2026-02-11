match(char **list, char *val) {
    int i;

    for ( i=0; list[i]!=NULL; ++i )
	if ( strmatch(val,list[i])==0 )
return( i );

return( -1 );
}
