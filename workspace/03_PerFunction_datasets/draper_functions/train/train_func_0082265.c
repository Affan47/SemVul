pipe_unref (Pipe *p)
{
	if (p) {
		pipe_lock (p);
		p->ref_count--;
#ifdef DEBUG_NOTIFICATION
		g_print ("Pipe %p --: %u\n", p, p->ref_count);
#endif
		if (p->ref_count == 0) {

			GMutex *m = &(p->mutex);

			if (p->ioc)
				g_io_channel_unref (p->ioc);
#ifdef G_OS_WIN32
			if (p->fds[0] >= 0)
				_close (p->fds[0]);
			if (p->fds[1] >= 0)
				_close (p->fds[1]);
#else
			if (p->fds[0] >= 0)
				close (p->fds[0]);
			if (p->fds[1] >= 0)
				close (p->fds[1]);
#endif

#ifdef DEBUG_NOTIFICATION
			g_print ("Destroyed Pipe %p\n", p);
#endif
			g_free (p);

			g_mutex_unlock (m);
			g_mutex_clear (m);
		}
		else
			pipe_unlock (p);
	}
}
