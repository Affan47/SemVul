my_ElementDeclHandler(void *userData,
                      const XML_Char *name,
                      XML_Content *model)
{
    xmlparseobject *self = (xmlparseobject *)userData;
    PyObject *args = NULL;

    if (have_handler(self, ElementDecl)) {
        PyObject *rv = NULL;
        PyObject *modelobj, *nameobj;

        if (PyErr_Occurred())
            return;

        if (flush_character_buffer(self) < 0)
            goto finally;
        modelobj = conv_content_model(model, (conv_string_to_unicode));
        if (modelobj == NULL) {
            flag_error(self);
            goto finally;
        }
        nameobj = string_intern(self, name);
        if (nameobj == NULL) {
            Py_DECREF(modelobj);
            flag_error(self);
            goto finally;
        }
        args = Py_BuildValue("NN", nameobj, modelobj);
        if (args == NULL) {
            Py_DECREF(modelobj);
            flag_error(self);
            goto finally;
        }
        self->in_callback = 1;
        rv = call_with_frame(getcode(ElementDecl, "ElementDecl", __LINE__),
                             self->handlers[ElementDecl], args, self);
        self->in_callback = 0;
        if (rv == NULL) {
            flag_error(self);
            goto finally;
        }
        Py_DECREF(rv);
    }
 finally:
    Py_XDECREF(args);
    XML_FreeContentModel(self->itself, model);
    return;
}
