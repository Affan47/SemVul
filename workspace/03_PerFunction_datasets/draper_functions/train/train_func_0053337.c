new_time_ex(int hour, int minute, int second, int usecond,
            PyObject *tzinfo, PyTypeObject *type)
{
    PyDateTime_Time *self;
    char aware = tzinfo != Py_None;

    self = (PyDateTime_Time *) (type->tp_alloc(type, aware));
    if (self != NULL) {
        self->hastzinfo = aware;
        self->hashcode = -1;
        TIME_SET_HOUR(self, hour);
        TIME_SET_MINUTE(self, minute);
        TIME_SET_SECOND(self, second);
        TIME_SET_MICROSECOND(self, usecond);
        if (aware) {
            Py_INCREF(tzinfo);
            self->tzinfo = tzinfo;
        }
    }
    return (PyObject *)self;
}
