fluid_player_load(fluid_player_t *player, fluid_playlist_item *item)
{
	fluid_midi_file *midifile;
	char* buffer;
	size_t buffer_length;
	int buffer_owned;

	if (item->filename != NULL) {
		fluid_file fp;

		FLUID_LOG(FLUID_DBG, "%s: %d: Loading midifile %s", __FILE__, __LINE__,
		          item->filename);

		fp = FLUID_FOPEN(item->filename, "rb");
		if (fp == NULL) {
			FLUID_LOG(FLUID_ERR, "Couldn't open the MIDI file");
			return FLUID_FAILED;
		}
		buffer = fluid_file_read_full(fp, &buffer_length);
		if (buffer == NULL) {
			FLUID_FCLOSE(fp);
			return FLUID_FAILED;
		}
		buffer_owned = 1;
		FLUID_FCLOSE(fp);
	} else {

		FLUID_LOG(FLUID_DBG, "%s: %d: Loading midifile from memory (%p)",
		          __FILE__, __LINE__, item->buffer);
		buffer = (char *) item->buffer;
		buffer_length = item->buffer_len;

		buffer_owned = 0;
	}

	midifile = new_fluid_midi_file(buffer, buffer_length);
	if (midifile == NULL) {
		if (buffer_owned) {
			FLUID_FREE(buffer);
		}
		return FLUID_FAILED;
	}
	player->division = fluid_midi_file_get_division(midifile);
	fluid_player_set_midi_tempo(player, player->miditempo);


	if (fluid_midi_file_load_tracks(midifile, player) != FLUID_OK) {
		if (buffer_owned) {
			FLUID_FREE(buffer);
		}
		delete_fluid_midi_file(midifile);
		return FLUID_FAILED;
	}
	delete_fluid_midi_file(midifile);
	if (buffer_owned) {
		FLUID_FREE(buffer);
	}
	return FLUID_OK;
}
