snd_mixer_oss_build(struct snd_mixer_oss *mixer)
{
	static struct snd_mixer_oss_assign_table table[] = {
		{ SOUND_MIXER_VOLUME, 	"Master",		0 },
		{ SOUND_MIXER_VOLUME, 	"Front",		0 },
		{ SOUND_MIXER_BASS,	"Tone Control - Bass",	0 },
		{ SOUND_MIXER_TREBLE,	"Tone Control - Treble", 0 },
		{ SOUND_MIXER_SYNTH,	"Synth",		0 },
		{ SOUND_MIXER_SYNTH,	"FM",			0 },
		{ SOUND_MIXER_SYNTH,	"Music",		0 },
		{ SOUND_MIXER_PCM,	"PCM",			0 },
		{ SOUND_MIXER_SPEAKER,	"Beep", 		0 },
		{ SOUND_MIXER_SPEAKER,	"PC Speaker", 		0 },
		{ SOUND_MIXER_SPEAKER,	"Speaker", 		0 },
		{ SOUND_MIXER_LINE,	"Line", 		0 },
		{ SOUND_MIXER_MIC,	"Mic", 			0 },
		{ SOUND_MIXER_CD,	"CD", 			0 },
		{ SOUND_MIXER_IMIX,	"Monitor Mix", 		0 },
		{ SOUND_MIXER_ALTPCM,	"PCM",			1 },
		{ SOUND_MIXER_ALTPCM,	"Headphone",		0 },
		{ SOUND_MIXER_ALTPCM,	"Wave",			0 },
		{ SOUND_MIXER_RECLEV,	"-- nothing --",	0 },
		{ SOUND_MIXER_IGAIN,	"Capture",		0 },
		{ SOUND_MIXER_OGAIN,	"Playback",		0 },
		{ SOUND_MIXER_LINE1,	"Aux",			0 },
		{ SOUND_MIXER_LINE2,	"Aux",			1 },
		{ SOUND_MIXER_LINE3,	"Aux",			2 },
		{ SOUND_MIXER_DIGITAL1,	"Digital",		0 },
		{ SOUND_MIXER_DIGITAL1,	"IEC958",		0 },
		{ SOUND_MIXER_DIGITAL1,	"IEC958 Optical",	0 },
		{ SOUND_MIXER_DIGITAL1,	"IEC958 Coaxial",	0 },
		{ SOUND_MIXER_DIGITAL2,	"Digital",		1 },
		{ SOUND_MIXER_DIGITAL3,	"Digital",		2 },
		{ SOUND_MIXER_PHONEIN,	"Phone",		0 },
		{ SOUND_MIXER_PHONEOUT,	"Master Mono",		0 },
		{ SOUND_MIXER_PHONEOUT,	"Speaker",		0 },
		{ SOUND_MIXER_PHONEOUT,	"Mono",			0 },
		{ SOUND_MIXER_PHONEOUT,	"Phone",		0 },
		{ SOUND_MIXER_VIDEO,	"Video",		0 },
		{ SOUND_MIXER_RADIO,	"Radio",		0 },
		{ SOUND_MIXER_MONITOR,	"Monitor",		0 }
	};
	unsigned int idx;

	for (idx = 0; idx < ARRAY_SIZE(table); idx++)
		snd_mixer_oss_build_input(mixer, &table[idx], 0, 0);
	if (mixer->mask_recsrc) {
		mixer->get_recsrc = snd_mixer_oss_get_recsrc2;
		mixer->put_recsrc = snd_mixer_oss_put_recsrc2;
	}
}
