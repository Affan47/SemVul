PyFF_registerImportExport(PyObject *self, PyObject *args) {
    PyObject *import, *export, *data;
    char *name, *exten, *exten_list=NULL;


    if ( !PyArg_ParseTuple(args,"OOOess|s", &import, &export, &data,
	    "UTF-8", &name, &exten, &exten_list ))
return( NULL );
    if ( import==Py_None && export==Py_None )
Py_RETURN_NONE;
    if ( import==Py_None )
	import=NULL;
    else if ( !PyCallable_Check(import) ) {
	PyErr_Format(PyExc_TypeError, "First argument is not callable" );
return( NULL );
    }
    if ( export==Py_None )
	export=NULL;
    else if ( !PyCallable_Check(export) ) {
	PyErr_Format(PyExc_TypeError, "Second argument is not callable" );
return( NULL );
    }

    Py_XINCREF(import);
    Py_XINCREF(export);
    Py_XINCREF(data);

    if ( ie_cnt>=ie_max )
	py_ie = grealloc(py_ie,((ie_max += 10)+1)*sizeof(struct python_import_export));
    py_ie[ie_cnt].import = import;
    py_ie[ie_cnt].export = export;
    py_ie[ie_cnt].data = data;
    py_ie[ie_cnt].name = name;
    py_ie[ie_cnt].extension = copy(exten);
    py_ie[ie_cnt].all_extensions = copy(exten_list==NULL ? exten : exten_list);
    ++ie_cnt;
    py_ie[ie_cnt].name = NULL;

Py_RETURN_NONE;
}
