PyFFCvt_Concat( PyObject *_c1, PyObject *_c2 ) {
    PyFF_Cvt *c1 = (PyFF_Cvt *) _c1, *c2 = (PyFF_Cvt *) _c2;
    PyObject *ret;
    Py_ssize_t len1, len2;
    int i;
    int is_cvt2;

    len1 = PyFFCvt_Length(_c1);
    if ( PyType_IsSubtype(&PyFF_CvtType,((PyObject *)c2)->ob_type) ) {
	len2 = PyFFCvt_Length(_c2);
	is_cvt2 = true;
    } else if ( PySequence_Check(_c2)) {
	is_cvt2 = false;
	len2 = PySequence_Size(_c2);
    } else {
	PyErr_Format(PyExc_TypeError, "The second argument must be either another cvt or a tuple of integers");
return( NULL );
    }
    ret = PyTuple_New(len1+len2);
    for ( i=0; i<len1; ++i )
	PyTuple_SetItem(ret,i,Py_BuildValue("i",memushort(c1->cvt->data,c1->cvt->len,i*sizeof(uint16))) );
    if ( is_cvt2 ) {
	for ( i=0; i<len2; ++i )
	    PyTuple_SetItem(ret,len1+i,Py_BuildValue("i",memushort(c2->cvt->data,c2->cvt->len,i*sizeof(uint16))) );
    } else {
	for ( i=0; i<len2; ++i )
	    PyTuple_SetItem(ret,len1+i,Py_BuildValue("i",PySequence_GetItem(_c2,i)));
    }
Py_RETURN( (PyObject *) ret );
}
