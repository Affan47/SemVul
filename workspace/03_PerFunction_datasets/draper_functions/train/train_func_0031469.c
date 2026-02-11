treebuilder_start(TreeBuilderObject* self, PyObject* args)
{
    PyObject* tag;
    PyObject* attrib = Py_None;
    if (!PyArg_ParseTuple(args, "O|O:start", &tag, &attrib))
        return NULL;

    return treebuilder_handle_start(self, tag, attrib);
}
