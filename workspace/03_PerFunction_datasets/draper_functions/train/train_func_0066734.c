zbarpygtk_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gtk")) != NULL) {
        _PyGtkWidget_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Widget");
        if (_PyGtkWidget_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Widget from gtk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk");
        return ;
    }
    if ((module = PyImport_ImportModule("gtk.gdk")) != NULL) {
        _PyGdkPixbuf_Type = (PyTypeObject *)PyObject_GetAttrString(module, "Pixbuf");
        if (_PyGdkPixbuf_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Pixbuf from gtk.gdk");
            return ;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk.gdk");
        return ;
    }


#line 215 "pygtk/zbarpygtk.c"
    pygobject_register_class(d, "ZBarGtk", ZBAR_TYPE_GTK, &PyZBarGtk_Type, Py_BuildValue("(O)", &PyGtkWidget_Type));
}
