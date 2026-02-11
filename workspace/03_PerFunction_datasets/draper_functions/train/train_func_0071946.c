iscsi_sysfs_get_session_state(char *state, int sid)
{
	char id[NAME_SIZE];

	snprintf(id, sizeof(id), ISCSI_SESSION_ID, sid);
	if (sysfs_get_str(id, ISCSI_SESSION_SUBSYS, "state", state,
			  SCSI_MAX_STATE_VALUE))
		return ISCSI_ERR_SYSFS_LOOKUP;
	return 0;
}
