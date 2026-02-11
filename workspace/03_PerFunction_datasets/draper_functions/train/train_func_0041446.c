PyGILState_Release(PyGILState_STATE oldstate)
{
    PyThreadState *tcur = (PyThreadState *)PyThread_get_key_value(
                                                            autoTLSkey);
    if (tcur == NULL)
        Py_FatalError("auto-releasing thread-state, "
                      "but no thread-state for this thread");


    if (! PyThreadState_IsCurrent(tcur))
        Py_FatalError("This thread state must be current when releasing");
    assert(PyThreadState_IsCurrent(tcur));
    --tcur->gilstate_counter;
    assert(tcur->gilstate_counter >= 0);


    if (tcur->gilstate_counter == 0) {

        assert(oldstate == PyGILState_UNLOCKED);
        PyThreadState_Clear(tcur);


        PyThreadState_DeleteCurrent();
    }

    else if (oldstate == PyGILState_UNLOCKED)
        PyEval_SaveThread();
}
