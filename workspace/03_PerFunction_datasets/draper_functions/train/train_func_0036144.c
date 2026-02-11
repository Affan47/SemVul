Document_iter(Document *self)
{
	Iter *iter;

	if (iks_type(self->doc) != IKS_TAG) {
		PyErr_SetString(PyExc_TypeError, "Cannot iterate over text nodes");
		return NULL;
	}

	iter = PyObject_New(Iter, &Iter_type);
	iter->doc = iks_child(self->doc);
	iter->ref = self->ref;
	iter->tags = 0;
	iter->tagname = NULL;
	return (PyObject *) iter;
}
