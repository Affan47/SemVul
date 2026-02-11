kset_param(uint64_t transport_handle, uint32_t sid, uint32_t cid,
	   enum iscsi_param param, void *value, int type)
{
	struct iscsi_uevent *ev;
	char *param_str;
	int rc, len;
	struct iovec iov[2];

	log_debug(7, "in %s", __FUNCTION__);

	memset(setparam_buf, 0, NLM_SETPARAM_DEFAULT_MAX);
	ev = (struct iscsi_uevent *)setparam_buf;
	ev->type = ISCSI_UEVENT_SET_PARAM;
	ev->transport_handle = transport_handle;
	ev->u.set_param.sid = sid;
	ev->u.set_param.cid = cid;
	ev->u.set_param.param = param;

	param_str = setparam_buf + sizeof(*ev);
	switch (type) {
	case ISCSI_INT:
		sprintf(param_str, "%d", *((int *)value));
		break;
	case ISCSI_UINT:
		sprintf(param_str, "%u", *((unsigned int *)value));
		break;
	case ISCSI_STRING:
		if (!strlen(value))
			return 0;
		sprintf(param_str, "%s", (char *)value);
		break;
	default:
		log_error("invalid type %d", type);
		return -EINVAL;
	}
	ev->u.set_param.len = len = strlen(param_str) + 1;

	iov[1].iov_base = ev;
	iov[1].iov_len = sizeof(*ev) + len;
	rc = __kipc_call(iov, 2);
	if (rc < 0)
		return rc;

	return 0;
}
