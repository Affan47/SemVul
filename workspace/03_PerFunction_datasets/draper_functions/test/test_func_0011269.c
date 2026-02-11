smack_shm_shmctl(struct shmid_kernel *shp, int cmd)
{
	int may;

	switch (cmd) {
	case IPC_STAT:
	case SHM_STAT:
		may = MAY_READ;
		break;
	case IPC_SET:
	case SHM_LOCK:
	case SHM_UNLOCK:
	case IPC_RMID:
		may = MAY_READWRITE;
		break;
	case IPC_INFO:
	case SHM_INFO:


		return 0;
	default:
		return -EINVAL;
	}
	return smk_curacc_shm(shp, may);
}
