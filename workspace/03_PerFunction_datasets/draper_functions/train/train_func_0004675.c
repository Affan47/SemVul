print_sem (int semid)
{
	struct semid_ds semds;
	struct ipc_perm *ipcp = &semds.sem_perm;
	union semun arg;
	size_t i;

	arg.buf = &semds;
	if (semctl (semid, 0, IPC_STAT, arg) < 0)
		err(EXIT_FAILURE, _("semctl failed"));

	printf (_("\nSemaphore Array semid=%d\n"), semid);
	printf (_("uid=%u\t gid=%u\t cuid=%u\t cgid=%u\n"),
		ipcp->uid, ipcp->gid, ipcp->cuid, ipcp->cgid);
	printf (_("mode=%#o, access_perms=%#o\n"),
		ipcp->mode, ipcp->mode & 0777);
	printf (_("nsems = %ld\n"), (long) semds.sem_nsems);
	printf (_("otime = %-26.24s\n"),
		semds.sem_otime ? ctime (&semds.sem_otime) : _("Not set"));
	printf (_("ctime = %-26.24s\n"), ctime (&semds.sem_ctime));

	printf ("%-10s %-10s %-10s %-10s %-10s\n",
		_("semnum"),_("value"),_("ncount"),_("zcount"),_("pid"));
	arg.val = 0;
	for (i=0; i< semds.sem_nsems; i++) {
		int val, ncnt, zcnt, pid;
		val = semctl (semid, i, GETVAL, arg);
		ncnt = semctl (semid, i, GETNCNT, arg);
		zcnt = semctl (semid, i, GETZCNT, arg);
		pid = semctl (semid, i, GETPID, arg);
		if (val < 0 || ncnt < 0 || zcnt < 0 || pid < 0)
			err(EXIT_FAILURE, _("semctl failed"));

		printf ("%-10zd %-10d %-10d %-10d %-10d\n",
			i, val, ncnt, zcnt, pid);
	}
	printf ("\n");
	return;
}
