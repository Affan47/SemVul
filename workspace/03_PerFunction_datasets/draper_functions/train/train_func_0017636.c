reload_instance (string file, string classname, PyObject * args)
{

    PyObject *module = python::import_module (file);
    if (!module) return false;


    PyObject *reload = PyImport_ReloadModule (module);
    Py_DECREF (module);
    if (!reload) return false;

    return instanciate (reload, file, classname, args);
}
