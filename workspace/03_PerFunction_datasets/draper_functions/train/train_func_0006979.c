PyFFGlyph_AddExtrema(PyFF_Glyph *self, PyObject *args) {
    int emsize = 1000;
    char *flag = NULL;
    int ae = ae_only_good;
    SplineChar *sc = self->sc;
    SplineFont *sf = sc->parent;

    if ( !PyArg_ParseTuple(args,"|si", &flag, &emsize ) )
return( NULL );
    if ( flag!=NULL )
	ae = FlagsFromString(flag,addextremaflags);

    SplineCharAddExtrema(sc,sc->layers[self->layer].splines,ae,sf->ascent+sf->descent);
    SCCharChangedUpdate(sc,self->layer);
Py_RETURN( self );
}
