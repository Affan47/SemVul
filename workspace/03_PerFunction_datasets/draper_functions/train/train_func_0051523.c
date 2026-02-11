Stream_dealloc(Stream *self)
{
	if (self->jid) { Py_DECREF(self->jid); }
	iks_parser_delete(self->parser);
	self->ob_type->tp_free((PyObject *) self);
}
