onPatch(PORT localPort) {
	if (localPort <= 0) return;

	pthread_mutex_lock(&channelLock);

    MixerChannel *C = new MixerChannel;
	C->state = STATE_STOP;
	C->cmpt = dynamic_cast<ComponentAudio*>(connectedDevice(localPort));
	C->data = new AudioPacket(PACKET_SAMPLES);
	C->port = localPort;
	channels[localPort] = C;

    ch_inactive[localPort] = C;

    pthread_mutex_unlock(&channelLock);
}
