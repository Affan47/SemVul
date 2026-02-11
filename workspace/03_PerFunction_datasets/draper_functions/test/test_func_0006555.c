set_midi_substream_names(struct snd_oxfw *oxfw,
				     struct snd_rawmidi_str *str)
{
	struct snd_rawmidi_substream *subs;

	list_for_each_entry(subs, &str->substreams, list) {
		snprintf(subs->name, sizeof(subs->name),
			 "%s MIDI %d",
			 oxfw->card->shortname, subs->number + 1);
	}
}
