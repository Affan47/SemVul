eexec_hexString(PyObject *self, PyObject *args)
{
	PyObject *_res = NULL;
	unsigned char * inbuf;
	unsigned char * outbuf;
	static const unsigned char hexchars[] = "0123456789ABCDEF";
	unsigned long i, insize;

	if (!PyArg_ParseTuple(args, "s#", &inbuf, &insize))
		return NULL;

	outbuf = malloc(2 * insize);
	if (outbuf == NULL) {
		PyErr_NoMemory();
		return NULL;
	}

	for (i = 0; i < insize; i++) {
		outbuf[2 * i] = hexchars[(inbuf[i] >> 4) & 0xF];
		outbuf[2 * i + 1] = hexchars[inbuf[i] & 0xF];
	}
	_res = Py_BuildValue("s#", outbuf, 2 * insize);
	free(outbuf);
	return _res;
}
