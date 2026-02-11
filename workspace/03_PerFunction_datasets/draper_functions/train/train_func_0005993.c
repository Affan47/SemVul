Py_EndInterpreter(PyThreadState *tstate)
{
    PyInterpreterState *interp = tstate->interp;

    if (tstate != PyThreadState_GET())
        Py_FatalError("Py_EndInterpreter: thread is not current");
    if (tstate->frame != NULL)
        Py_FatalError("Py_EndInterpreter: thread still has a frame");
    if (tstate != interp->tstate_head || tstate->next != NULL)
        Py_FatalError("Py_EndInterpreter: not the last thread");

    PyImport_Cleanup();
    PyInterpreterState_Clear(interp);
    PyThreadState_Swap(NULL);
    PyInterpreterState_Delete(interp);
}
