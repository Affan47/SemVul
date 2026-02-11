ocfs2_control_validate_protocol(struct file *file,
					       const char __user *buf,
					       size_t count)
{
	ssize_t ret;
	char kbuf[OCFS2_CONTROL_PROTO_LEN];

	ret = ocfs2_control_cfu(kbuf, OCFS2_CONTROL_PROTO_LEN,
				buf, count);
	if (ret)
		return ret;

	if (strncmp(kbuf, OCFS2_CONTROL_PROTO, OCFS2_CONTROL_PROTO_LEN))
		return -EINVAL;

	ocfs2_control_set_handshake_state(file,
					  OCFS2_CONTROL_HANDSHAKE_PROTOCOL);

	return count;
}
