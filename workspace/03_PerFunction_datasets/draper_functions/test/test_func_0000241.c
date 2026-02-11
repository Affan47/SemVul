istgt_uctl_cmd_noop(UCTL_Ptr uctl)
{
	int rc;

	istgt_uctl_snprintf(uctl, "OK %s\n", uctl->cmd);
	rc = istgt_uctl_writeline(uctl);
	if (rc != UCTL_CMD_OK) {
		return rc;
	}
	return UCTL_CMD_OK;
}
