shm_setup(void)
{
	if  ((Ctrl_chan = msgget(MSGID, 0)) < 0)  {
		html_disperror(8101);
		exit(E_NOTRUN);
	}

#ifndef	USING_FLOCK
	if  ((Sem_chan = semget(SEMID, SEMNUMS, IPC_MODE)) < 0)  {
		html_disperror(8121);
		exit(E_SETUP);
	}
#endif

	if  (!jobshminit(0))  {
		html_disperror(8107);
		exit(E_JOBQ);
	}

	if  (!ptrshminit(0))  {
		print_error(8108);
		exit(E_PRINQ);
	}
}
