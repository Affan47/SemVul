Thread_Stop(GF_Thread *t, Bool Destroy)
{
	if (gf_th_status(t) == GF_THREAD_STATUS_RUN) {
#ifdef WIN32
		if (Destroy) {
			DWORD dw = 1;
			BOOL ret = TerminateThread(t->threadH, dw);
			if (!ret) {
				DWORD err = GetLastError();
				GF_LOG(GF_LOG_ERROR, GF_LOG_MUTEX, ("[Thread %s] Couldn't stop thread ID 0x%08x, error code %d\n", t->log_name, t->id, err));
			}
			t->threadH = NULL;
		} else {
			WaitForSingleObject(t->threadH, INFINITE);
		}
#else
		if (Destroy) {
#ifdef GPAC_ANDROID
			if (pthread_kill(t->threadH, SIGQUIT))
#else
			if (pthread_cancel(t->threadH))
#endif
				GF_LOG(GF_LOG_ERROR, GF_LOG_MUTEX, ("[Thread %s] Couldn't kill thread ID 0x%08x\n", t->log_name, t->id));
			t->threadH = 0;
		} else {

			if (pthread_join(t->threadH, NULL))
				GF_LOG(GF_LOG_ERROR, GF_LOG_MUTEX, ("[Thread %s] pthread_join() returned an error with thread ID 0x%08x\n", t->log_name, t->id));
		}
#endif
	}
	t->status = GF_THREAD_STATUS_DEAD;
}
