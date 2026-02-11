PyFF_AWGlyph_dealloc(PyFF_AWGlyph *self) {
    Py_XDECREF(self->left);
    Py_XDECREF(self->right);
    if ( self->base!=NULL ) {
	self->base->python_data = NULL;
	self->base = NULL;
    }
    self->ob_type->tp_free((PyObject *) self);
}
