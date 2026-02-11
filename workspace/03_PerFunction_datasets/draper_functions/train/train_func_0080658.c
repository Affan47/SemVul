lola_proc_codec_rw_write(struct snd_info_entry *entry,
				     struct snd_info_buffer *buffer)
{
	struct lola *chip = entry->private_data;
	char line[64];
	unsigned int id, verb, data, extdata;
	while (!snd_info_get_line(buffer, line, sizeof(line))) {
		if (sscanf(line, "%u %u %u %u", &id, &verb, &data, &extdata) != 4)
			continue;
		lola_codec_read(chip, id, verb, data, extdata,
				&chip->debug_res,
				&chip->debug_res_ex);
	}
}
