Crossfire_Player_dealloc(PyObject *obj) {
    Crossfire_Player *self;

    self = (Crossfire_Player *)obj;
    if (self) {
        if (self->obj) {
            free_object_assoc(self->obj);
        }
        Py_TYPE(self)->tp_free(obj);
    }
}
