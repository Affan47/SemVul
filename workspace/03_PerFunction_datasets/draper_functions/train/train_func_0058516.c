PyFF_SCImport(SplineChar *sc,int ie_index,char *filename,
	int layer, int clear) {
    int toback = layer!=ly_fore;
    PyObject *arglist, *result, *glyph = PySC_From_SC(sc);

    if ( ie_index>=ie_cnt )
return;
    SCPreserveLayer(sc,layer,false);
    if ( clear ) {
	SplinePointListsFree(sc->layers[layer].splines);
	sc->layers[layer].splines = NULL;
    }

    sc_active_in_ui = sc;
    layer_active_in_ui = layer;

    arglist = PyTuple_New(4);
    Py_XINCREF(py_ie[ie_index].data);
    Py_XINCREF(glyph);
    PyTuple_SetItem(arglist,0,py_ie[ie_index].data);
    PyTuple_SetItem(arglist,1,glyph);
    PyTuple_SetItem(arglist,2,DECODE_UTF8(filename,strlen(filename),NULL));
    PyTuple_SetItem(arglist,3,Py_BuildValue("i",toback));
    result = PyEval_CallObject(py_ie[ie_index].import, arglist);
    Py_DECREF(arglist);
    Py_XDECREF(result);
    if ( PyErr_Occurred()!=NULL )
	PyErr_Print();
}
