pyt_exec_str(RESULT * result, const char *module, const char *function, int argc, const char *argv[])
{

    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    const char *rv = NULL;
    int i;

    pName = PyString_FromString(module);


    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
	pDict = PyModule_GetDict(pModule);


	pFunc = PyDict_GetItemString(pDict, function);


	if (pFunc && PyCallable_Check(pFunc)) {
	    pArgs = PyTuple_New(argc);
	    for (i = 0; i < argc; ++i) {
		pValue = PyString_FromString(argv[i]);
		if (!pValue) {
		    Py_DECREF(pArgs);
		    Py_DECREF(pModule);
		    error("Cannot convert argument \"%s\" to python format", argv[i]);
		    SetResult(&result, R_STRING, "");
		    return;
		}

		PyTuple_SetItem(pArgs, i, pValue);
	    }
	    pValue = PyObject_CallObject(pFunc, pArgs);
	    Py_DECREF(pArgs);
	    if (pValue != NULL) {
		rv = PyString_AsString(pValue);
		SetResult(&result, R_STRING, rv);
		Py_DECREF(pValue);

		return;
	    } else {
		Py_DECREF(pModule);
		error("Python call failed (\"%s.%s\")", module, function);

		PyErr_PrintEx(0);
		SetResult(&result, R_STRING, "");
		return;
	    }

	} else {
	    error("Can not find python function \"%s.%s\"", module, function);
	}
	Py_DECREF(pModule);
    } else {
	error("Failed to load python module \"%s\"", module);

	PyErr_PrintEx(0);
    }
    SetResult(&result, R_STRING, "");
    return;
}
