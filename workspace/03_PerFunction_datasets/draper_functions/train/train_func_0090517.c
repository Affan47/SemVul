statusfunc (int status)
{
	if (status == -1)
		return 0;
	if (status == -2)
		return 10;
#if 1
	if (cdrom_audiostatus != status) {
		if (status == AUDIO_STATUS_IN_PROGRESS) {
			cdrom_playing = 1;
			cdrom_audiotimeout = 1;
		}
		if (cdrom_playing && status != AUDIO_STATUS_IN_PROGRESS && status != AUDIO_STATUS_PAUSED && status != AUDIO_STATUS_NOT_SUPPORTED) {
			cdrom_audiotimeout = -1;
		}
	}
	cdrom_audiostatus = status;
#endif
	return 0;
}
