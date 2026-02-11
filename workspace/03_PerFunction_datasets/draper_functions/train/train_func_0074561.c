_GResource_FindResName(char *name) {
    int top=rsummit, bottom = rbase;
    int test, cmp;

    if ( rcur==0 )
return( -1 );

    forever {
	if ( top==bottom )
return( -1 );
	test = (top+bottom)/2;
	cmp = strcmp(name,_GResource_Res[test].res+rskiplen);
	if ( cmp==0 )
return( test );
	if ( test==bottom )
return( -1 );
	if ( cmp>0 )
	    bottom=test+1;
	else
	    top = test;
    }
}
