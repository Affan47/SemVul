throwTypeError(const char *name, PyObject *object)
{
    PyObject *tuple = Py_BuildValue("(ssO)", "while calling", name, object);

    PyErr_SetObject(PyExc_TypeError, tuple);
    Py_DECREF(tuple);

    env->get_vm_env()->ThrowNew(env->getPythonExceptionClass(), "type error");
}
