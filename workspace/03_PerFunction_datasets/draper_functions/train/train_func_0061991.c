intel_pmc_ipc_simple_command(int cmd, int sub)
{
	int ret;

	mutex_lock(&ipclock);
	if (ipcdev.dev == NULL) {
		mutex_unlock(&ipclock);
		return -ENODEV;
	}
	ipc_send_command(sub << IPC_CMD_SUBCMD | cmd);
	ret = intel_pmc_ipc_check_status();
	mutex_unlock(&ipclock);

	return ret;
}
