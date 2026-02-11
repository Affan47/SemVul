onUnpatch(PORT localPort) {
	if (localPort <= 0) return;


	pthread_mutex_lock(&channelLock);


	ch_inactive.erase(localPort);
	ch_active.erase(localPort);


	delete channels[localPort]->data;
	delete channels[localPort];
	channels.erase(localPort);


	pthread_mutex_unlock(&channelLock);
}
