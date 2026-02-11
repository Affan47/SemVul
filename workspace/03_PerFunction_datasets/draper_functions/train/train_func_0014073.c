getAudio(AudioPacket* buffer) {
	pthread_mutex_lock(&channelLock);
    unsigned short N = ch_active.size();

	map<PORT,MixerChannel*>::iterator x = ch_active.begin();
    while (x != ch_active.end()) {
		(*x).second->cmpt->getAudio((*x).second->data);
		x++;
    }

	short **chs = new short*[N];

	short *mix = buffer->getData();

	x = ch_active.begin();
	unsigned int i = 0;
    while (x != ch_active.end()) {
        chs[i] = (*x).second->data->getData();
		x++;
		i++;
    }


    short M = 32768;
    double factor;

    for (unsigned int k = 0; k < PACKET_SAMPLES; k++) {

        mix[k] = 0;
        for (unsigned int i = 0; i < N; i++) {

            factor = 1.0;


            for (unsigned int j = i+1; j < N; j++) {
                factor *= (1.0 - fabs(double(chs[j][k])/M));
            }

			mix[k] += short(chs[i][k]*factor);
        }
    }
    delete[] chs;


	x = ch_active.begin();
	while (x != ch_active.end()) {
		if ((*x).second->state == STATE_STOP) {
			PORT p = (*x).second->port;
			ch_inactive[p] = ch_active[p];
			ch_active.erase(p);
		}
		x++;
	}

	pthread_mutex_unlock(&channelLock);
}
