__plain_param_set(u32 tid, u64 sid, int type,
			   u32 partial, struct iscsi_param *param, int update)
{
	int err;

	err = ki->param_set(tid, sid, type, partial, param);
	if (err < 0) {
		log_error ("unable to set parameter (%d:%u) of session %#" PRIx64 " in target %u: %d",
			type, partial, sid, tid, errno);
		return err;
	}

	if (update)
		;

	return err;
}
