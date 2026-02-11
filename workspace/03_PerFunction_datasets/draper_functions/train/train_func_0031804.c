init_xmlextra(void) {
static int initialized = 0;
PyObject *m, *d;

	if (initialized != 0) return;
#if 1
	SaxReaderType.ob_type = &PyType_Type;
#else
	PreparsingReaderType.ob_type = &PyType_Type;
#endif
	m = Py_InitModule((char *) "_xmlextra", xmlextraMethods);
	d = PyModule_GetDict(m);
	MyError = PyErr_NewException("_xmlextra.error", NULL, NULL);
	PyDict_SetItemString(d, "error", MyError);
	PyDict_SetItemString(d, "__docformat__", PyString_FromString("restructuredtext en"));
	PyDict_SetItemString(d, "__doc__",
			PyString_FromString("Special libxml2 extensions for PyXMPP internal use."));
	initialized = 1;
}
