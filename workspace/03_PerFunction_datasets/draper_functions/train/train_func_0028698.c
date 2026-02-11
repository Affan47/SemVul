get_lock()
{
	struct sembuf operations[1];

	operations[0].sem_num = 0;
	operations[0].sem_op = -1;
	operations[0].sem_flg = 0;
	if (semop(sem_id, operations, 1) == -1) {
		perror("semop");


		shmdt(shm_degree);

		shmctl(shm_id1, IPC_RMID, NULL);
		shmctl(shm_id2, IPC_RMID, NULL);
		semctl(sem_id, 0, IPC_RMID);

		exit(1);
	}
	printf("[%d] dop %d\n", getpid(), *shm_degree);
}
