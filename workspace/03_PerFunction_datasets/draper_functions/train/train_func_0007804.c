_setup_srun_task_launch_detection(void)
{
	int retries = 0;
	pthread_t tid;
        pthread_attr_t attr;

        pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        while ((errno = pthread_create(&tid, &attr,
				       &_task_launch_detection, NULL))) {
                if (++retries > 5) {
                        error ("mpi/pmi2: pthread_create error %m");
                        slurm_attr_destroy(&attr);
                        return SLURM_ERROR;
                }
                sleep(1);
        }
        slurm_attr_destroy(&attr);
        debug("mpi/pmi2: task launch detection thread (%lu) started",
	      (unsigned long) tid);

        return SLURM_SUCCESS;
}
