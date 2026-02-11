style_sound_free(gpointer data, gpointer userdata)
{
	START_FUNC
	struct sound *sound=(struct sound *)data;
	if (sound) {
		if (sound->match) g_regex_unref(sound->match);
		if (sound->press) g_free(sound->press);
		if (sound->release) g_free(sound->release);
		if (sound->hover) g_free(sound->hover);
		g_free(sound);
	}
	END_FUNC
}
