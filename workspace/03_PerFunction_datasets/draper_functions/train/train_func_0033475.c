expat_start_doctype_handler(XMLParserObject *self,
                            const XML_Char *doctype_name,
                            const XML_Char *sysid,
                            const XML_Char *pubid,
                            int has_internal_subset)
{
    PyObject *self_pyobj = (PyObject *)self;
    PyObject *doctype_name_obj, *sysid_obj, *pubid_obj;
    PyObject *parser_doctype = NULL;
    PyObject *res = NULL;

    if (PyErr_Occurred())
        return;

    doctype_name_obj = makeuniversal(self, doctype_name);
    if (!doctype_name_obj)
        return;

    if (sysid) {
        sysid_obj = makeuniversal(self, sysid);
        if (!sysid_obj) {
            Py_DECREF(doctype_name_obj);
            return;
        }
    } else {
        Py_INCREF(Py_None);
        sysid_obj = Py_None;
    }

    if (pubid) {
        pubid_obj = makeuniversal(self, pubid);
        if (!pubid_obj) {
            Py_DECREF(doctype_name_obj);
            Py_DECREF(sysid_obj);
            return;
        }
    } else {
        Py_INCREF(Py_None);
        pubid_obj = Py_None;
    }


    if (self->handle_doctype) {
        res = PyObject_CallFunction(self->handle_doctype, "OOO",
                                    doctype_name_obj, pubid_obj, sysid_obj);
        Py_CLEAR(res);
    }


    parser_doctype = PyObject_GetAttrString(self_pyobj, "doctype");
    if (parser_doctype) {
        if (!XMLParser_CheckExact(self_pyobj)) {
            if (PyErr_WarnEx(PyExc_DeprecationWarning,
                            "This method of XMLParser is deprecated.  Define"
                            " doctype() method on the TreeBuilder target.",
                            1) < 0) {
                goto clear;
            }
            res = PyObject_CallFunction(parser_doctype, "OOO",
                                        doctype_name_obj, pubid_obj, sysid_obj);
            Py_CLEAR(res);
        }
    }

clear:
    Py_XDECREF(parser_doctype);
    Py_DECREF(doctype_name_obj);
    Py_DECREF(pubid_obj);
    Py_DECREF(sysid_obj);
}
