unixHandler(int sig)
	{
		Q_UNUSED(sig);
		unsigned char c = 0;
		if(::write(g_pq->d->sig_pipe[1], &c, 1) == -1)
		{

			return;
		}
	}
