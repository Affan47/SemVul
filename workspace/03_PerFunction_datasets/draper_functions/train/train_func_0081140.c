isuniname(char *name) {
    int i;
    if ( name[0]!='u' || name[1]!='n' || name[2]!='i' )
return( false );
    for ( i=3; i<7; ++i )
	if ( name[i]<'0' || (name[i]>'9' && name[i]<'A') || name[i]>'F' )
return( false );
    if ( name[7]!='\0' )
return( false );

return( true );
}
