SFFindLayerIndexByName(SplineFont *sf,char *name) {
    int l;

    if ( name!=NULL ) {
	for ( l=0; l<sf->layer_cnt; ++l ) {
	    if ( strcmp(sf->layers[l].name,name)==0 )
return( l );
	}
    }
    PyErr_Format(PyExc_ValueError, "Bad layer name: %s", name );
return( -1 );
}
