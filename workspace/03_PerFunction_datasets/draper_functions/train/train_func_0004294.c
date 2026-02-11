PyFFFont_replaceAll(PyObject *self, PyObject *args) {
    FontViewBase *fv = ((PyFF_Font *) self)->fv;
    PyObject *srch, *rpl;
    SplineSet *srch_ss, *rpl_ss;
    double err = .01;

    if ( !PyArg_ParseTuple(args,"OO|d", &srch, &rpl, &err ))
return( NULL );

    if ( PyType_IsSubtype(&PyFF_LayerType,((PyObject *)srch)->ob_type) ) {
	srch_ss = SSFromLayer((PyFF_Layer *) srch);
    } else if ( PyType_IsSubtype(&PyFF_ContourType,((PyObject *)srch)->ob_type) ) {
	srch_ss = SSFromContour((PyFF_Contour *) srch, NULL);
    } else {
	PyErr_Format(PyExc_TypeError, "Unexpected type");
return( NULL );
    }

    if ( PyType_IsSubtype(&PyFF_LayerType,((PyObject *)rpl)->ob_type) ) {
	rpl_ss = SSFromLayer((PyFF_Layer *) rpl);
    } else if ( PyType_IsSubtype(&PyFF_ContourType,((PyObject *)rpl)->ob_type) ) {
	rpl_ss = SSFromContour((PyFF_Contour *) rpl, NULL);
    } else {
	PyErr_Format(PyExc_TypeError, "Unexpected type");
return( NULL );
    }


return( Py_BuildValue( "i", FVReplaceAll(fv,srch_ss,rpl_ss,err,sv_reverse|sv_flips)));
}
