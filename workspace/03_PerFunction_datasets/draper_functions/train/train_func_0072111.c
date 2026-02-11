PyFF_Font_set_int2(PyFF_Font *self,PyObject *value,
	char *str,int offset) {
    long temp;

    if ( value==NULL ) {
	PyErr_Format(PyExc_TypeError, "Cannot delete the %s", str);
return( -1 );
    }
    temp = PyInt_AsLong(value);
    if ( PyErr_Occurred()!=NULL )
return( -1 );
    * (int16 *) (((char *) (self->fv->sf)) + offset ) = temp;
return( 0 );
}
