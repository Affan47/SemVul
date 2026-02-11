mgt_shm_atexit(void)
{


	if (getpid() != mgt_pid)
		return;
	if (heritage.vsm != NULL)
		VSM_common_delete(&heritage.vsm);
}
