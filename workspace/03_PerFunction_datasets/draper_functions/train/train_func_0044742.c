PyFF_PrivateIndex( PyObject *self, PyObject *index ) {
    SplineFont *sf = ((PyFF_Private *) self)->sf;
    struct psdict *private = sf->private;
    char *value=NULL;
    char *pt, *end;
    double temp;
    PyObject *tuple;

    if ( STRING_CHECK(index)) {
#if PY_MAJOR_VERSION >= 3
    char *name;
    PyObject *bytes = PyUnicode_AsUTF8String(index);
    if ( bytes==NULL )
return( NULL );
    name = PyBytes_AsString(bytes);
	if ( private!=NULL )
	    value = PSDictHasEntry(private,name);
    Py_DECREF(bytes);
#else
	char *name = PyBytes_AsString(index);
	if ( private!=NULL )
	    value = PSDictHasEntry(private,name);
#endif
    } else {
	PyErr_Format(PyExc_TypeError, "Index must be a string" );
return( NULL );
    }
    if ( value==NULL ) {
	PyErr_Format(PyExc_TypeError, "No such entry" );
return( NULL );
    }
    strtod(value,&end); while ( *end==' ' ) ++end;
    if ( *end=='\0' )
return( Py_BuildValue("d",strtod(value,NULL)) );

    if ( *value=='[' ) {
	int cnt = 0;
	pt = value+1;
	forever {
	    strtod(pt,&end);
	    if ( pt==end )
	break;
	    ++cnt;
	    pt = end;
	}
	while ( *pt==' ' ) ++pt;
	if ( *pt==']' ) {
	    tuple = PyTuple_New(cnt);
	    cnt = 0;
	    pt = value+1;
	    forever {
		temp = strtod(pt,&end);
		if ( pt==end )
	    break;
		PyTuple_SetItem(tuple,cnt++,Py_BuildValue("d",temp));
		pt = end;
	    }
return( tuple );
	}
    }
return( Py_BuildValue("s",value));
}
