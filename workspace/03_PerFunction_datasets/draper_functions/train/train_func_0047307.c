A_PlayTone(gpointer data)
{
	D_PlayTone *d = (D_PlayTone *) data;
	gn_tone tone;
	gn_data gdat;
	gn_error error;
	static int uadj = -1;

	gn_data_clear(&gdat);

	pthread_mutex_lock(&ringtoneMutex);
	tone.frequency = d->frequency;
	tone.volume = d->volume;
	gdat.tone = &tone;

	if (uadj < 0) {
		struct timeval t1, t2, dt;

		gettimeofday(&t1, NULL);
		error = gn_sm_functions(GN_OP_PlayTone, &gdat, statemachine);
		gettimeofday(&t2, NULL);
		timersub(&t2, &t1, &dt);
		uadj = 2 * dt.tv_usec;
	} else {
		error = gn_sm_functions(GN_OP_PlayTone, &gdat, statemachine);
	}
	if (d->usec > 0) {
		if (d->usec > uadj) usleep(d->usec - uadj);
		tone.frequency = 0;
		tone.volume = 0;
		gn_sm_functions(GN_OP_PlayTone, &gdat, statemachine);
	}

	pthread_cond_signal(&ringtoneCond);
	pthread_mutex_unlock(&ringtoneMutex);

	return error;
}
