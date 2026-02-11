ipc_sync_callback(IPC_CMD_PARMS) {

	if (parent == 1)
		return 0;

	if (len < (int) sizeof(ipc_sync)) {
		_MSG("IPC sync handler got a short sync block", MSGFLAG_ERROR);
		return -1;
	}

	((IPCRemote *) auxptr)->SyncIPCCmd((ipc_sync *) data);

	return 0;
}
