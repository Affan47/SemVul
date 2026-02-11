create_new_element(PyObject* tag, PyObject* attrib)
{
    ElementObject* self;

    self = PyObject_GC_New(ElementObject, &Element_Type);
    if (self == NULL)
        return NULL;


    if (PyDict_CheckExact(attrib) && !PyDict_Size(attrib))
        attrib = Py_None;

    self->extra = NULL;

    if (attrib != Py_None) {
        if (create_extra(self, attrib) < 0) {
            PyObject_Del(self);
            return NULL;
        }
    }

    Py_INCREF(tag);
    self->tag = tag;

    Py_INCREF(Py_None);
    self->text = Py_None;

    Py_INCREF(Py_None);
    self->tail = Py_None;

    self->weakreflist = NULL;

    ALLOC(sizeof(ElementObject), "create element");
    PyObject_GC_Track(self);
    return (PyObject*) self;
}
