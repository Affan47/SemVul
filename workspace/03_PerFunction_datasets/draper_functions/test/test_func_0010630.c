_PyGILState_Reinit(void)
{
    PyThreadState *tstate = PyGILState_GetThisThreadState();
    PyThread_delete_key(autoTLSkey);
    if ((autoTLSkey = PyThread_create_key()) == -1)
        Py_FatalError("Could not allocate TLS entry");


    if (tstate && PyThread_set_key_value(autoTLSkey, (void *)tstate) < 0)
        Py_FatalError("Couldn't create autoTLSkey mapping");
}
