add_wsq (void)
{
	int i;
	MonoWSQ *wsq;

	EnterCriticalSection (&wsqs_lock);
	wsq = mono_wsq_create ();
	if (wsqs == NULL) {
		LeaveCriticalSection (&wsqs_lock);
		return NULL;
	}
	for (i = 0; i < wsqs->len; i++) {
		if (g_ptr_array_index (wsqs, i) == NULL) {
			wsqs->pdata [i] = wsq;
			LeaveCriticalSection (&wsqs_lock);
			return wsq;
		}
	}
	g_ptr_array_add (wsqs, wsq);
	LeaveCriticalSection (&wsqs_lock);
	return wsq;
}
