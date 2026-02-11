unistim_register(struct unistimsession *s)
{
	struct unistim_device *d;

	ast_mutex_lock(&devicelock);
	d = devices;
	while (d) {
		if (!strcasecmp(s->macaddr, d->id)) {

			s->device = d;
			d->session = s;
			d->codec_number = DEFAULT_CODEC;
			d->missed_call = 0;
			d->receiver_state = STATE_ONHOOK;
			break;
		}
		d = d->next;
	}
	ast_mutex_unlock(&devicelock);

	if (!d) {
		return 0;
	}

	return 1;
}
