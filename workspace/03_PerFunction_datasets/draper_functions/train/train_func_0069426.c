PyFF_PrivateIndexAssign( PyObject *self, PyObject *index, PyObject *value ) {
    SplineFont *sf = ((PyFF_Private *) self)->sf;
    struct psdict *private = sf->private;
    char *string, *freeme=NULL;
    char buffer[40];

    if ( STRING_CHECK(value))
	string = PyBytes_AsString(index);
    else if ( PyFloat_Check(value)) {
	double temp = PyFloat_AsDouble(value);
	sprintf(buffer,"%g",temp);
	string = buffer;
    } else if ( PyInt_Check(value)) {
	int temp = PyInt_AsLong(value);
	sprintf(buffer,"%d",temp);
	string = buffer;
    } else if ( PySequence_Check(value)) {
	int i; char *pt;
	pt = string = freeme = galloc(PySequence_Size(value)*21+4);
	*pt++ = '[';
	for ( i=0; i<PySequence_Size(value); ++i ) {
	    sprintf( pt, "%g", PyFloat_AsDouble(PySequence_GetItem(value,i)));
	    pt += strlen(pt);
	    *pt++ = ' ';
	}
	if ( pt[-1]==' ' ) --pt;
	*pt++ = ']'; *pt = '\0';
    } else {
	PyErr_Format(PyExc_TypeError, "Tuple expected for argument" );
return( -1 );
    }

    if ( STRING_CHECK(index)) {
	char *name = PyBytes_AsString(index);
	if ( private==NULL )
	    sf->private = private = gcalloc(1,sizeof(struct psdict));
	PSDictChangeEntry(private,name,string);
    } else {
	free(freeme);
	PyErr_Format(PyExc_TypeError, "Index must be a string" );
return( -1 );
    }
return( 0 );
}
