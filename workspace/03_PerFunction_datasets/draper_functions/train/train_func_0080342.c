configure_sound_device()
{
	int fragment = 0x00020008;
	int format = AFMT_U8;
	int channels = 2;
	int speed = 44100;

	if (ioctl(audio_fd, SNDCTL_DSP_SETFMT, &format) == -1) {
		perror("SNDCTL_DSP_SETFMT");
	}
	if (ioctl(audio_fd, SNDCTL_DSP_CHANNELS, &channels) == -1) {
		perror("SNDCTL_DSP_CHANNELS");
	}
	if (ioctl(audio_fd, SNDCTL_DSP_SPEED, &speed) == -1) {
		perror("SNDCTL_DSP_SPEED");
	}
	if( ioctl(audio_fd, SNDCTL_DSP_SETFRAGMENT, &fragment) == -1 ) {
		perror("SNDCTL_DSP_SETFRAGMENT");
	}

	sound_enabled = true;
}
