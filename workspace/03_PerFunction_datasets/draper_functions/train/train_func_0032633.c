bcmdec_create_shmem(GstBcmDec *bcmdec, int *shmem_id)
{
	int shmid = -1;
	key_t shmkey = BCM_GST_SHMEM_KEY;
	shmid_ds buf;

	if (shmem_id == NULL) {
		GST_ERROR_OBJECT(bcmdec, "Invalid argument ...");
		return BC_STS_INSUFF_RES;
	}

	*shmem_id = shmid;


	shmid = shmget(shmkey, 1024, 0644 | IPC_CREAT | IPC_EXCL);
	if (shmid == -1) {
		if (errno == EEXIST) {
			GST_DEBUG_OBJECT(bcmdec, "bcmdec_create_shmem:shmem already exists :%d", errno);
			shmid = shmget(shmkey, 1024, 0644);
			if (shmid == -1) {
				GST_ERROR_OBJECT(bcmdec, "bcmdec_create_shmem:unable to get shmid :%d", errno);
				return BC_STS_INSUFF_RES;
			}


			if (shmctl(shmid,IPC_STAT,&buf) == -1) {
				GST_ERROR_OBJECT(bcmdec, "bcmdec_create_shmem:shmctl failed ...");
				return BC_STS_ERROR;
			}

			if (buf.shm_nattch == 0) {
				sem_destroy(&g_inst_sts->inst_ctrl_event);

				if (shmctl(shmid, IPC_RMID, NULL) != -1)
						GST_DEBUG_OBJECT(bcmdec, "bcmdec_create_shmem:deleted shmem segment and creating a new one ...");

				shmid = shmget(shmkey, 1024, 0644 | IPC_CREAT | IPC_EXCL);
				if (shmid == -1) {
					GST_ERROR_OBJECT(bcmdec, "bcmdec_create_shmem:unable to get shmid :%d", errno);
					return BC_STS_INSUFF_RES;
				}

				bcmdec_get_shmem(bcmdec, shmid, TRUE);

			} else {

				bcmdec_get_shmem(bcmdec, shmid, FALSE);
			}

		} else {
			GST_ERROR_OBJECT(bcmdec, "shmcreate failed with err %d",errno);
			return BC_STS_ERROR;
		}
	} else {

		bcmdec_get_shmem(bcmdec, shmid, TRUE);
	}

	*shmem_id = shmid;

	return BC_STS_SUCCESS;
}
