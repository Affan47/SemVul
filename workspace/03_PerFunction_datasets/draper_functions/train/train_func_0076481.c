print_shm(int shmid)
{
	struct shmid_ds shmds;
	struct ipc_perm *ipcp = &shmds.shm_perm;

	if (shmctl(shmid, IPC_STAT, &shmds) == -1) {
		bb_perror_msg("shmctl");
		return;
	}

	printf("\nShared memory Segment shmid=%d\n"
			  "uid=%d\tgid=%d\tcuid=%d\tcgid=%d\n"
			  "mode=%#o\taccess_perms=%#o\n"
			  "bytes=%ld\tlpid=%d\tcpid=%d\tnattch=%ld\n",
			  shmid,
			  ipcp->uid, ipcp->gid, ipcp->cuid, ipcp->cgid,
			  ipcp->mode, ipcp->mode & 0777,
			  (long) shmds.shm_segsz, shmds.shm_lpid, shmds.shm_cpid,
			  (long) shmds.shm_nattch);
	printf("att_time=%-26.24s\n",
			  shmds.shm_atime ? ctime(&shmds.shm_atime) : "Not set");
	printf("det_time=%-26.24s\n",
			  shmds.shm_dtime ? ctime(&shmds.shm_dtime) : "Not set");
	printf("change_time=%-26.24s\n\n", ctime(&shmds.shm_ctime));
}
