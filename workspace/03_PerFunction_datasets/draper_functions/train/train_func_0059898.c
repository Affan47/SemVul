GlyphListToStr(PyObject *value) {
    char *str, *pt;
    int i,cnt,len;

    if ( !PySequence_Check(value)) {
	PyErr_Format(PyExc_TypeError, "Value must be a sequence" );
return( NULL );
    }
    if ( PyBytes_Check(value)) {
	str = PyBytes_AsString(value);
#if PY_MAJOR_VERSION >= 3
    } else if ( PyUnicode_Check(value)) {
	value = PyUnicode_AsUTF8String(value);
	str = PyBytes_AsString(value);
	Py_DECREF(value);
#endif
    } else {
	cnt = PySequence_Size(value);
	len = 0;
	for ( i=0; i<cnt; ++i ) {
	    PyObject *obj = PySequence_GetItem(value,i);
	    if ( PyType_IsSubtype(&PyFF_GlyphType,((PyObject *)obj)->ob_type) ) {
		PyFF_Glyph *g = (PyFF_Glyph *) obj;
		len += strlen(g->sc->name) + 1;
	    } else {
		PyErr_Format(PyExc_TypeError, "Must be a sequence of glyphs" );
return( NULL );
	    }
	}
	pt = str = galloc(len+1);
	for ( i=0; i<cnt; ++i ) {
	    PyObject *obj = PySequence_GetItem(value,i);
	    PyFF_Glyph *g = (PyFF_Glyph *) obj;
	    strcpy(pt,g->sc->name);
	    pt += strlen(g->sc->name);
	    strcpy(pt," ");
	    pt += 1;
	}
	if ( pt>str ) pt[-1] = '\0';
    }
return( str );
}
