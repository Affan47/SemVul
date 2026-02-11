dlmc_fs_result(int fd, char *name, int *type, int *nodeid, int *result)
{
	struct dlmc_header h;
	int rv;

	rv = do_read(fd, &h, sizeof(h));
	if (rv < 0)
		goto out;

	strncpy(name, h.name, DLM_LOCKSPACE_LEN);
	*nodeid = h.option;
	*result = h.data;

	switch (h.command) {
	case DLMC_CMD_FS_REGISTER:
		*type = DLMC_RESULT_REGISTER;
		break;
	case DLMC_CMD_FS_NOTIFIED:
		*type = DLMC_RESULT_NOTIFIED;
		break;
	default:
		*type = 0;
	}
 out:
	return rv;
}
