PyFFFont_lookupSetFlags(PyObject *self, PyObject *args) {
    SplineFont *sf = ((PyFF_Font *) self)->fv->sf;
    OTLookup *otl;
    char *lookup;
    PyObject *flagtuple;
    int flags;

    if ( !PyArg_ParseTuple(args,"sO", &lookup, &flagtuple ))
return( NULL );

    otl = SFFindLookup(sf,lookup);
    if ( otl==NULL ) {
	PyErr_Format(PyExc_EnvironmentError, "No lookup named %s", lookup );
return( NULL );
    }

    flags = ParseLookupFlags(sf,flagtuple);
    if ( flags==-1 )
return( NULL );

    otl->lookup_flags = flags;
Py_RETURN( self );
}
