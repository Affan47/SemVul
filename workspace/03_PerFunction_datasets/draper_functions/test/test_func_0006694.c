do_warn(PyObject *message, PyObject *category, Py_ssize_t stack_level)
{
    PyObject *filename, *module, *registry, *res;
    int lineno;

    if (!setup_context(stack_level, &filename, &lineno, &module, &registry))
        return NULL;

    res = warn_explicit(category, message, filename, lineno, module, registry,
                        NULL);
    Py_DECREF(filename);
    Py_DECREF(registry);
    Py_DECREF(module);
    return res;
}
