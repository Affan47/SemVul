pysqlite_connection_exit(pysqlite_Connection* self, PyObject* args)
{
    PyObject* exc_type, *exc_value, *exc_tb;
    char* method_name;
    PyObject* result;

    if (!PyArg_ParseTuple(args, "OOO", &exc_type, &exc_value, &exc_tb)) {
        return NULL;
    }

    if (exc_type == Py_None && exc_value == Py_None && exc_tb == Py_None) {
        method_name = "commit";
    } else {
        method_name = "rollback";
    }

    result = PyObject_CallMethod((PyObject*)self, method_name, "");
    if (!result) {
        return NULL;
    }
    Py_DECREF(result);

    Py_RETURN_FALSE;
}
