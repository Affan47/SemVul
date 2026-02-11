posix_fexecve(PyObject *self, PyObject *args)
{
    int fd;
    PyObject *argv, *env;
    char **argvlist;
    char **envlist;
    Py_ssize_t argc, envc;

    if (!PyArg_ParseTuple(args, "iOO:fexecve",
                          &fd, &argv, &env))
        return NULL;
    if (!PyList_Check(argv) && !PyTuple_Check(argv)) {
        PyErr_SetString(PyExc_TypeError,
                        "fexecve() arg 2 must be a tuple or list");
        return NULL;
    }
    argc = PySequence_Size(argv);
    if (!PyMapping_Check(env)) {
        PyErr_SetString(PyExc_TypeError,
                        "fexecve() arg 3 must be a mapping object");
        return NULL;
    }

    argvlist = parse_arglist(argv, &argc);
    if (argvlist == NULL)
        return NULL;

    envlist = parse_envlist(env, &envc);
    if (envlist == NULL)
        goto fail;

    fexecve(fd, argvlist, envlist);


    (void) posix_error();

    while (--envc >= 0)
        PyMem_DEL(envlist[envc]);
    PyMem_DEL(envlist);
  fail:
    free_string_array(argvlist, argc);
    return NULL;
}
