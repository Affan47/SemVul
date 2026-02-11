style_sound_matches(struct sound *sound, const gchar *name)
{
	START_FUNC
	gboolean ret;
	if (name) {
		if (sound->match)
			ret=g_regex_match(sound->match, name,
				G_REGEX_MATCH_ANCHORED|G_REGEX_MATCH_NOTEMPTY, NULL);
		else ret=TRUE;
	}
	else ret=FALSE;
	END_FUNC
	return ret;
}
