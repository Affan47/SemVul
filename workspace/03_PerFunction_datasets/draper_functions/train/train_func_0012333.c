wsm_suspend_resume_indication(struct cw1200_common *priv,
					 int link_id, struct wsm_buf *buf)
{
	u32 flags;
	struct wsm_suspend_resume arg;

	flags = WSM_GET32(buf);
	arg.link_id = link_id;
	arg.stop = !(flags & 1);
	arg.multicast = !!(flags & 8);
	arg.queue = (flags >> 1) & 3;

	cw1200_suspend_resume(priv, &arg);

	return 0;

underflow:
	return -EINVAL;
}
