load_binpersid(Unpicklerobject *self)
{
    PyObject *pid = 0;

    if (self->pers_func) {
        PDATA_POP(self->stack, pid);
        if (! pid) return -1;

        if (PyList_Check(self->pers_func)) {
            if (PyList_Append(self->pers_func, pid) < 0) {
                Py_DECREF(pid);
                return -1;
            }
        }
        else {
            ARG_TUP(self, pid);
            if (self->arg) {
                pid = PyObject_Call(self->pers_func, self->arg,
                                    NULL);
                FREE_ARG_TUP(self);
            }
            if (! pid) return -1;
        }

        PDATA_PUSH(self->stack, pid, -1);
        return 0;
    }
    else {
        PyErr_SetString(UnpicklingError,
                        "A load persistent id instruction was encountered,\n"
                        "but no persistent_load function was specified.");
        return -1;
    }
}
