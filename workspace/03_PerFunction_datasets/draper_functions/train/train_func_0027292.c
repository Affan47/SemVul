xmlparser_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    XMLParserObject *self = (XMLParserObject *)type->tp_alloc(type, 0);
    if (self) {
        self->parser = NULL;
        self->target = self->entity = self->names = NULL;
        self->handle_start = self->handle_data = self->handle_end = NULL;
        self->handle_comment = self->handle_pi = self->handle_close = NULL;
        self->handle_doctype = NULL;
    }
    return (PyObject *)self;
}
