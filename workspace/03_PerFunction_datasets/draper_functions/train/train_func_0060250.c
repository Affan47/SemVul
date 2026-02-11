brief_load_voice_file(int voice_num, char *name)
{
	int load_attempts = 0;
	while(1) {

		if ( load_attempts++ > 5 ) {
			break;
		}

		Brief_voices[voice_num] = audiostream_open( name, ASF_VOICE );
		if ( Brief_voices[voice_num] >= 0 ) {
			break;
		}


		if ( Game_mode & GM_MULTIPLAYER ) {
			break;
		}
	}
}
