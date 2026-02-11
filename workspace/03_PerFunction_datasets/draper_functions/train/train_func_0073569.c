TupleOfGlyphNames(char *str,int extras) {
    int cnt;
    char *pt, *start;
    PyObject *tuple;
    int ch;

    for ( pt=str; *pt==' '; ++pt );
    if ( *pt=='\0' )
return( PyTuple_New(extras));

    for ( cnt=1; *pt; ++pt ) {
	if ( *pt==' ' ) {
	    ++cnt;
	    while ( pt[1]==' ' ) ++pt;
	}
    }
    tuple = PyTuple_New(extras+cnt);
    for ( pt=str, cnt=0; *pt; ) {
	while ( *pt==' ' ) ++pt;
	if ( *pt=='\0' )
    break;
	start = pt;
	while ( *pt!=' ' && *pt!='\0' ) ++pt;
	ch = *pt; *pt = '\0';
	PyTuple_SetItem(tuple,extras+cnt,STRING_TO_PY(start));
	*pt = ch;
	++cnt;
    }
return( tuple );
}
