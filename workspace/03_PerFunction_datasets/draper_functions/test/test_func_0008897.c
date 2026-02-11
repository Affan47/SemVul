clean_up()
{
	if (shm_data)
		if (shmdt(shm_data) < 0)
			fprintf(stderr, "Failed to detach shared memory: %s\n", strerror(errno));

	if (shm != -1)
		if (shmctl(shm, IPC_RMID, NULL) < 0)
			fprintf(stderr, "Failed to remove shared memory segment: %s\n", strerror(errno));

	if (sem != -1)
		if (semctl(sem, 0, IPC_RMID) < 0)
			die("semctl");
}
