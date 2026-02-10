fromRGB565(PyObject *self, PyObject *args){
	guchar* rgbdata;
	gint width, height;
	gint swap_bytes;
	gint rotate;
	gchar* savefilename;
	gint rgbdatalen;
	if(!PyArg_ParseTuple(args, "s#iiiis", &rgbdata, &rgbdatalen, &width, &height, &swap_bytes, &rotate, &savefilename)){
		printf("Argh! Failed to parse tuple!\n");
		exit(1);
	}
       	fromRGB565C(rgbdata, width, height, swap_bytes, rotate, savefilename);
	Py_INCREF(Py_None);
	return Py_None;
}
