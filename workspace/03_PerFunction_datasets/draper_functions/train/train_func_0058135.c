_pickle_Unpickler_load_impl(UnpicklerObject *self)

{
    UnpicklerObject *unpickler = (UnpicklerObject*)self;


    if (unpickler->read == NULL) {
        PickleState *st = _Pickle_GetGlobalState();
        PyErr_Format(st->UnpicklingError,
                     "Unpickler.__init__() was not called by %s.__init__()",
                     Py_TYPE(unpickler)->tp_name);
        return NULL;
    }

    return load(unpickler);
}
