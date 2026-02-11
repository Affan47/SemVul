PyFFFont_appendSFNTName(PyObject *self, PyObject *args) {
    SplineFont *sf = ((PyFF_Font *) self)->fv->sf;
    struct ttflangname dummy;
    int i;

    memset(&dummy,0,sizeof(dummy));
    DefaultTTFEnglishNames(&dummy, sf);

    if ( !SetSFNTName(sf,args,&dummy) )
return( NULL );

    for ( i=0; i<ttf_namemax; ++i )
	free( dummy.names[i]);

Py_RETURN( self );
}
