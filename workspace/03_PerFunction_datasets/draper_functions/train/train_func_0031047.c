PyFF_RefArrayIndex( PyObject *self, PyObject *index ) {
    SplineChar *sc = ((PyFF_RefArray *) self)->sc;
    int layer;

    if ( STRING_CHECK(index)) {
#if PY_MAJOR_VERSION >= 3
    char *name;
    PyObject *bytes = PyUnicode_AsUTF8String(index);
    if( bytes==NULL )
return( NULL );
    name = PyBytes_AsString(bytes);
	layer = SFFindLayerIndexByName(sc->parent,name);
    Py_DECREF( bytes );
#else
	char *name = PyBytes_AsString(index);
	layer = SFFindLayerIndexByName(sc->parent,name);
#endif
	if ( layer<0 )
return( NULL );
    } else if ( PyInt_Check(index)) {
	layer = PyInt_AsLong(index);
    } else {
	PyErr_Format(PyExc_TypeError, "Index must be a layer name or index" );
return( NULL );
    }
return( PyFF_Glyph_get_layer_references((PyFF_Glyph *) PySC_From_SC(sc),NULL,layer));
}
