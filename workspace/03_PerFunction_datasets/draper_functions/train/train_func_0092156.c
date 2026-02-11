PyFFGlyph_Build(PyObject *self, PyObject *args) {
    SplineChar *sc = ((PyFF_Glyph *) self)->sc;
    int layer = ((PyFF_Glyph *) self)->layer;

    if ( SFIsSomethingBuildable(sc->parent,sc,layer,false) )
	SCBuildComposit(sc->parent,sc,layer,NULL,true);

Py_RETURN( self );
}
