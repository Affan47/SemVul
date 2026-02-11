xmlparse_ExternalEntityParserCreate(xmlparseobject *self, PyObject *args)
{
    char *context;
    char *encoding = NULL;
    xmlparseobject *new_parser;
    int i;

    if (!PyArg_ParseTuple(args, "z|s:ExternalEntityParserCreate",
                          &context, &encoding)) {
        return NULL;
    }

    new_parser = PyObject_GC_New(xmlparseobject, &Xmlparsetype);
    if (new_parser == NULL)
        return NULL;
    new_parser->buffer_size = self->buffer_size;
    new_parser->buffer_used = 0;
    new_parser->buffer = NULL;
    new_parser->ordered_attributes = self->ordered_attributes;
    new_parser->specified_attributes = self->specified_attributes;
    new_parser->in_callback = 0;
    new_parser->ns_prefixes = self->ns_prefixes;
    new_parser->itself = XML_ExternalEntityParserCreate(self->itself, context,
                                                        encoding);
    new_parser->handlers = 0;
    new_parser->intern = self->intern;
    Py_XINCREF(new_parser->intern);
    PyObject_GC_Track(new_parser);

    if (self->buffer != NULL) {
        new_parser->buffer = malloc(new_parser->buffer_size);
        if (new_parser->buffer == NULL) {
            Py_DECREF(new_parser);
            return PyErr_NoMemory();
        }
    }
    if (!new_parser->itself) {
        Py_DECREF(new_parser);
        return PyErr_NoMemory();
    }

    XML_SetUserData(new_parser->itself, (void *)new_parser);


    for (i = 0; handler_info[i].name != NULL; i++)
        ;

    new_parser->handlers = malloc(sizeof(PyObject *) * i);
    if (!new_parser->handlers) {
        Py_DECREF(new_parser);
        return PyErr_NoMemory();
    }
    clear_handlers(new_parser, 1);


    for (i = 0; handler_info[i].name != NULL; i++) {
        PyObject *handler = self->handlers[i];
        if (handler != NULL) {
            Py_INCREF(handler);
            new_parser->handlers[i] = handler;
            handler_info[i].setter(new_parser->itself,
                                   handler_info[i].handler);
        }
    }
    return (PyObject *)new_parser;
}
