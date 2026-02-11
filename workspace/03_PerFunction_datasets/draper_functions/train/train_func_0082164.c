pti_release_masterchannel(struct pti_masterchannel *mc)
{
	u8 master, channel, i;

	mutex_lock(&alloclock);

	if (mc) {
		master = mc->master;
		channel = mc->channel;

		if (master == APP_BASE_ID) {
			i = channel >> 3;
			drv_data->ia_app[i] &=  ~(0x80>>(channel & 0x7));
		} else if (master == OS_BASE_ID) {
			i = channel >> 3;
			drv_data->ia_os[i] &= ~(0x80>>(channel & 0x7));
		} else {
			i = channel >> 3;
			drv_data->ia_modem[i] &= ~(0x80>>(channel & 0x7));
		}

		kfree(mc);
	}

	mutex_unlock(&alloclock);
}
