_PyFF_Font_set_real(SplineFont *sf,PyObject *value,
	char *str,int offset) {
    double temp;

    if ( value==NULL ) {
	PyErr_Format(PyExc_TypeError, "Cannot delete the %s", str);
return( -1 );
    }
    temp = PyFloat_AsDouble(value);
    if ( PyErr_Occurred()!=NULL )
return( -1 );
    * (real *) (((char *) sf) + offset ) = temp;
return( 0 );
}
