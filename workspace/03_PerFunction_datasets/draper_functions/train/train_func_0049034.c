fluid_synth_get_channel_info (fluid_synth_t *synth, int chan,
                              fluid_synth_channel_info_t *info)
{
	fluid_channel_t *channel;
	fluid_preset_t *preset;
	char *name;

	if (info) {
		info->assigned = FALSE;
		info->name[0] = '\0';
	}

	fluid_return_val_if_fail (info != NULL, FLUID_FAILED);
	FLUID_API_ENTRY_CHAN(FLUID_FAILED);

	channel = synth->channel[chan];
	preset = channel->preset;

	if (preset) {
		info->assigned = TRUE;
		name = fluid_preset_get_name (preset);

		if (name) {
			strncpy (info->name, name, FLUID_SYNTH_CHANNEL_INFO_NAME_SIZE);
			info->name[FLUID_SYNTH_CHANNEL_INFO_NAME_SIZE - 1] = '\0';
		} else info->name[0] = '\0';

		info->sfont_id = preset->sfont->id;
		info->bank = fluid_preset_get_banknum (preset);
		info->program = fluid_preset_get_num (preset);
	} else {
		info->assigned = FALSE;
		fluid_channel_get_sfont_bank_prog (channel, &info->sfont_id, &info->bank, &info->program);
		info->name[0] = '\0';
	}

	fluid_synth_api_exit(synth);
	return FLUID_OK;
}
