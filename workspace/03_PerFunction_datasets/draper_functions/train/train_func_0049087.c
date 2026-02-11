vcs_notifier(struct notifier_block *nb, unsigned long code, void *_param)
{
	struct vt_notifier_param *param = _param;
	struct vc_data *vc = param->vc;
	struct vcs_poll_data *poll =
		container_of(nb, struct vcs_poll_data, notifier);
	int currcons = poll->cons_num;

	if (code != VT_UPDATE)
		return NOTIFY_DONE;

	if (currcons == 0)
		currcons = fg_console;
	else
		currcons--;
	if (currcons != vc->vc_num)
		return NOTIFY_DONE;

	poll->seen_last_update = false;
	wake_up_interruptible(&poll->waitq);
	kill_fasync(&poll->fasync, SIGIO, POLL_IN);
	return NOTIFY_OK;
}
