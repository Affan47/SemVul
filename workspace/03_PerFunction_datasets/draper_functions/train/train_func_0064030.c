log_flush(void)
{
	struct sembuf ops;

	if (!la)
		return;

	while (!la->empty) {
		ops.sem_num = 0;
		ops.sem_flg = 0;
		ops.sem_op = -1;
		if (semop(la->semid, &ops, 1) < 0) {
			syslog(LOG_ERR, "semop up failed");
			exit(1);
		}

		log_dequeue(la->buff);

		ops.sem_op = 1;
		if (semop(la->semid, &ops, 1) < 0) {
			syslog(LOG_ERR, "semop down failed");
			exit(1);
		}
		log_syslog(la->buff);
	}
}
