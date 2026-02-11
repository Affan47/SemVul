Util_ReleaseThread(PyThreadState *tstate)
{
	PyThreadState *old_tstate;
	if (tstate == NULL)
		Py_FatalError("PyEval_ReleaseThread: NULL thread state");
	old_tstate = PyThreadState_Swap(NULL);
	if (old_tstate != tstate && old_tstate != NULL)
		Py_FatalError("PyEval_ReleaseThread: wrong thread state");
	PyEval_ReleaseLock();
}
