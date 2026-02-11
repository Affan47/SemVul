initMixer() {
	enabled = (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 1024) >= 0);
	if (enabled) {
		Mix_AllocateChannels(MIXER_NUMBER_CHANNELS);
		reservedChannels = Mix_ReserveChannels( MIXER_RESERVED_CHANNELS );
		if ( MIXER_RESERVED_CHANNELS != reservedChannels )
			cout << "reserve channels not successfull: reserved: " << reservedChannels << endl;
		lastUsedReservedChannel = 0;
		fn2snd.clear();
		fn2mus.clear();
		playsOn.clear();
	}
}
