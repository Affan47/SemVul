expat_default_handler(XMLParserObject* self, const XML_Char* data_in,
                      int data_len)
{
    PyObject* key;
    PyObject* value;
    PyObject* res;

    if (data_len < 2 || data_in[0] != '&')
        return;

    key = PyUnicode_DecodeUTF8(data_in + 1, data_len - 2, "strict");
    if (!key)
        return;

    value = PyDict_GetItem(self->entity, key);

    if (value) {
        if (TreeBuilder_CheckExact(self->target))
            res = treebuilder_handle_data(
                (TreeBuilderObject*) self->target, value
                );
        else if (self->handle_data)
            res = PyObject_CallFunction(self->handle_data, "O", value);
        else
            res = NULL;
        Py_XDECREF(res);
    } else if (!PyErr_Occurred()) {

        char message[128] = "undefined entity ";
        strncat(message, data_in, data_len < 100?data_len:100);
        expat_set_error(
            XML_ERROR_UNDEFINED_ENTITY,
            EXPAT(GetErrorLineNumber)(self->parser),
            EXPAT(GetErrorColumnNumber)(self->parser),
            message
            );
    }

    Py_DECREF(key);
}
