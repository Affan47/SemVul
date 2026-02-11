detail_encode(rad_listen_t *this, UNUSED REQUEST *request)
{
	listen_detail_t *data = this->data;


	if (!data->signal) {
		int delay = (data->poll_interval - 1) * USEC;


		delay += (USEC * 3) / 4;
		delay += fr_rand() % (USEC / 2);

		DEBUG2("Detail listener %s state %s signalled %d waiting %d.%06d sec",
		       data->filename,
		       fr_int2str(state_names, data->state, "?"), data->signal,
		       (delay / USEC), delay % USEC);

		return delay;
	}

	data->signal = 0;

	DEBUG2("Detail listener %s state %s signalled %d waiting %d.%06d sec",
	       data->filename, fr_int2str(state_names, data->state, "?"),
	       data->signal,
	       data->delay_time / USEC,
	       data->delay_time % USEC);

	return data->delay_time;
}
