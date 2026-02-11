message_play_wave( message_q *q )
{
	int index;
	MissionMessage *m;
	char filename[MAX_FILENAME_LEN];

	m = &Messages[q->message_num];

	if ( m->wave_info.index >= 0 ) {
		index = m->wave_info.index;
		strcpy_s( filename, Message_waves[index].name );


		if (fsspeech_play_from(FSSPEECH_FROM_INGAME) && message_filename_is_generic(filename))
			return false;


		if ( q->flags & MQF_CONVERT_TO_COMMAND ) {
			char *p, new_filename[MAX_FILENAME_LEN];

			Message_waves[index].num = -1;


			p = strchr(filename, '_' );
			if ( p == NULL ) {
				mprintf(("Cannot convert %s to terran command wave -- find Sandeep or Allender\n", Message_waves[index].name));
				return false;
			}


			p++;
			strcpy_s( new_filename, COMMAND_WAVE_PREFIX );
			strcat_s( new_filename, p );
			strcpy_s( filename, new_filename );
		}


		message_load_wave(index, filename);
		if ( Message_waves[index].num == -1 ) {
			m->wave_info.index = -1;
		}

		if ( m->wave_info.index >= 0 ) {

			Message_wave_duration = snd_get_duration(Message_waves[index].num);
			Playing_messages[Num_messages_playing].wave = snd_play_raw( Message_waves[index].num, 0.0f );

			return (Playing_messages[Num_messages_playing].wave != -1);
		}
	}

	return false;
}
