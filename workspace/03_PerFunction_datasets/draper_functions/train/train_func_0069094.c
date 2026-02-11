delwaitpid(int pid)
{
	int r, w;

	for(r=w=0; r<nwaitpids; r++)
		if(waitpids[r] != pid)
			waitpids[w++] = waitpids[r];
	nwaitpids = w;
}
