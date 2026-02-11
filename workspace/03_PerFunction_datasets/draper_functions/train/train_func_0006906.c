FlagsFromString(char *str,struct flaglist *flags) {
    uint32 i;
    for ( i=0; flags[i].name!=NULL; ++i )
	if ( strcmp(str,flags[i].name)==0 )
return( flags[i].flag );

    PyErr_Format( PyExc_TypeError, "Unknown flag %s", str );
return( PYFF_FLAG_UNKNOWN );
}
