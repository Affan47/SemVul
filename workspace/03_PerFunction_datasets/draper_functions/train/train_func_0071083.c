delete_fluid_rampreset (fluid_rampreset_t* preset)
{
	int err = FLUID_OK;
	fluid_preset_zone_t* zone;
	fluid_rampreset_voice_t *data;

	if (preset->global_zone != NULL) {
		if (delete_fluid_preset_zone(preset->global_zone) != FLUID_OK) {
			err = FLUID_FAILED;
		}
		preset->global_zone = NULL;
	}
	zone = preset->zone;
	while (zone != NULL) {
		preset->zone = zone->next;
		if (delete_fluid_preset_zone(zone) != FLUID_OK) {
			err = FLUID_FAILED;
		}
		zone = preset->zone;
	}

	if (preset->presetvoices != NULL) {
		fluid_list_t *tmp = preset->presetvoices, *next;
		while (tmp) {
			data = (fluid_rampreset_voice_t *)(tmp->data);
			FLUID_FREE(data);

			next = tmp->next;
			FLUID_FREE(tmp);
			tmp = next;
		}
	}
	preset->presetvoices = NULL;

	FLUID_FREE(preset);
	return err;
}
