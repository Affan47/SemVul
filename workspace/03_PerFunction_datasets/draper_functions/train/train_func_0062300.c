ipc_err_string(int error)
{
	if (error == IPC_PUNIT_ERR_SUCCESS)
		return "no error";
	else if (error == IPC_PUNIT_ERR_INVALID_CMD)
		return "invalid command";
	else if (error == IPC_PUNIT_ERR_INVALID_PARAMETER)
		return "invalid parameter";
	else if (error == IPC_PUNIT_ERR_CMD_TIMEOUT)
		return "command timeout";
	else if (error == IPC_PUNIT_ERR_CMD_LOCKED)
		return "command locked";
	else if (error == IPC_PUNIT_ERR_INVALID_VR_ID)
		return "invalid vr id";
	else if (error == IPC_PUNIT_ERR_VR_ERR)
		return "vr error";
	else
		return "unknown error";
}
