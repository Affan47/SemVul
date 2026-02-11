_PyGILState_Init(PyInterpreterState *i, PyThreadState *t)
{
    assert(i && t);
    autoTLSkey = PyThread_create_key();
    if (autoTLSkey == -1)
        Py_FatalError("Could not allocate TLS entry");
    autoInterpreterState = i;
    assert(PyThread_get_key_value(autoTLSkey) == NULL);
    assert(t->gilstate_counter == 0);

    _PyGILState_NoteThreadState(t);
}
