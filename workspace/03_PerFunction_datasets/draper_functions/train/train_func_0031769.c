myFatalError(void *ctx, const char *msg, ...){
va_list vargs;
xmlParserCtxtPtr ctxt=(xmlParserCtxtPtr) ctx;
SaxReaderObject *reader=(SaxReaderObject *)ctxt->_private;
PyObject *str,*obj;

	va_start (vargs, msg);
	str=PyString_FromFormatV(msg,vargs);
	va_end (vargs);
	if (str==NULL) {
		reader->exception=1;
		return;
	}
	obj=PyObject_CallMethod(reader->handler,"error","O",str);
	Py_DECREF(str);
	if (obj==NULL) reader->exception=1;
	else Py_DECREF(obj);
}
