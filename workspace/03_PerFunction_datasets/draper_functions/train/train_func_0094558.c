snd_ctl_shm_get_power_state(snd_ctl_t *ctl, unsigned int *state)
{
	snd_ctl_shm_t *shm = ctl->private_data;
	volatile snd_ctl_shm_ctrl_t *ctrl = shm->ctrl;
	int err;
	ctrl->cmd = SNDRV_CTL_IOCTL_POWER_STATE;
	err = snd_ctl_shm_action(ctl);
	if (err < 0)
		return err;
	*state = ctrl->u.power_state;
	return err;
}
