Crossfire_Map_dealloc(PyObject *obj) {
    Crossfire_Map *self;

    self = (Crossfire_Map *)obj;
    if (self) {
        if (self->map && self->valid) {
            free_map_assoc(self->map);
        }
        Py_TYPE(self)->tp_free(obj);
    }
}
