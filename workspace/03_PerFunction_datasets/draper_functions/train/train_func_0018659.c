red_alert_voice_load()
{
	Assert( Briefing != NULL );
	if ( strnicmp(Briefing->stages[0].voice, NOX("none"), 4) && (Briefing->stages[0].voice[0] != '\0') ) {
		Red_alert_voice = audiostream_open( Briefing->stages[0].voice, ASF_VOICE );
	}
}
