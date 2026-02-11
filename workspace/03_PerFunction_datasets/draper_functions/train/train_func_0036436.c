parasite_python_init(char **error)
{
#ifdef ENABLE_PYTHON
    struct sigaction old_sigint;
    PyObject *pygtk;

    if (is_blacklisted()) {
      *error = g_strdup("Application is blacklisted");
      return 0;
    }


    if (!dlopen(PYTHON_SHARED_LIB, RTLD_NOW | RTLD_GLOBAL))
    {
        *error = g_strdup_printf("Parasite: Error on dlopen(): %s\n", dlerror());
        return 0;
    }

    captured_stdout = g_string_new("");
    captured_stderr = g_string_new("");


    sigaction(SIGINT, NULL, &old_sigint);

    if (!Py_IsInitialized())
        Py_Initialize();

    sigaction(SIGINT, &old_sigint, NULL);

    Py_InitModule("parasite", parasite_python_methods);
    if(PyRun_SimpleString(
        "import parasite\n"
        "import sys\n"
        "\n"
        "class StdoutCatcher:\n"
        "    def write(self, str):\n"
        "        parasite.capture_stdout(str)\n"
        "    def flush(self):\n"
        "        pass\n"
        "\n"
        "class StderrCatcher:\n"
        "    def write(self, str):\n"
        "        parasite.capture_stderr(str)\n"
        "    def flush(self):\n"
        "        pass\n"
        "\n"
        "class StdinCatcher:\n"
        "    def readline(self, size=-1):\n"
        "        return parasite.capture_stdin(size)\n"
        "    def read(self, size=-1):\n"
        "        return parasite.capture_stdin(size)\n"
        "    def flush(self):\n"
        "        pass\n"
        "\n"
    ) == -1)
      return 0;

    if (!pygobject_init(-1, -1, -1))
        return 0;

    pygtk = PyImport_ImportModule("gtk");

    if (pygtk != NULL)
    {
        PyObject *module_dict = PyModule_GetDict(pygtk);
        PyObject *cobject = PyDict_GetItemString(module_dict, "_PyGtk_API");


        if (cobject != NULL)
        {
            if (PyCObject_Check(cobject))
                _PyGtk_API = (struct _PyGtk_FunctionStruct*)
                PyCObject_AsVoidPtr(cobject);
            else {
              *error = g_strdup("Parasite: Could not find _PyGtk_API object");
                return 0;
            }
        }
    } else {
        *error = g_strdup("Parasite: Could not import gtk");
        return 0;
    }

    python_enabled = TRUE;
#endif
    return !0;
}
