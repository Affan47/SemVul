check_prefs_changed_audio (void)
{
	int ch;

	if (sound_available) {
		ch = sound_prefs_changed ();
		if (ch > 0) {
#ifdef AVIOUTPUT
			AVIOutput_Restart ();
#endif
			clear_sound_buffers ();
		}
		if (ch) {
			set_audio ();
			audio_activate ();
		}
	}
#ifdef DRIVESOUND
	driveclick_check_prefs ();
#endif
}
