proc_read_formation(struct snd_info_entry *entry,
		struct snd_info_buffer *buffer)
{
	struct snd_bebob *bebob = entry->private_data;
	struct snd_bebob_stream_formation *formation;
	unsigned int i;

	snd_iprintf(buffer, "Output Stream from device:\n");
	snd_iprintf(buffer, "\tRate\tPCM\tMIDI\n");
	formation = bebob->tx_stream_formations;
	for (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) {
		snd_iprintf(buffer,
			    "\t%d\t%d\t%d\n", snd_bebob_rate_table[i],
			    formation[i].pcm, formation[i].midi);
	}

	snd_iprintf(buffer, "Input Stream to device:\n");
	snd_iprintf(buffer, "\tRate\tPCM\tMIDI\n");
	formation = bebob->rx_stream_formations;
	for (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) {
		snd_iprintf(buffer,
			    "\t%d\t%d\t%d\n", snd_bebob_rate_table[i],
			    formation[i].pcm, formation[i].midi);
	}
}
