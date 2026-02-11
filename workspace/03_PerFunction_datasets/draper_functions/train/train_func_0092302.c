process_does_match(gfarm_pid_t pid,
	gfarm_int32_t keytype, size_t keylen, char *sharedkey,
	struct process **processp)
{
	struct process *process = process_lookup((gfarm_int32_t)pid);

	if (process == NULL) {
		gflog_debug(GFARM_MSG_1001621,
			"process_lookup() failed");
		return (GFARM_ERR_NO_SUCH_PROCESS);
	}
	if (keytype != GFM_PROTO_PROCESS_KEY_TYPE_SHAREDSECRET ||
	    keylen != GFM_PROTO_PROCESS_KEY_LEN_SHAREDSECRET ||
	    memcmp(sharedkey, process->sharedkey,
	    GFM_PROTO_PROCESS_KEY_LEN_SHAREDSECRET) != 0) {
		gflog_debug(GFARM_MSG_1001622,
			"authentication failed");
		return (GFARM_ERR_AUTHENTICATION);
	}
	*processp = process;
	return (GFARM_ERR_NO_ERROR);
}
