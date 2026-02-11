fluid_ramsfont_sfont_get_preset(fluid_sfont_t* sfont, unsigned int bank, unsigned int prenum)
{
	fluid_preset_t* preset;
	fluid_rampreset_t* rampreset;

	rampreset = fluid_ramsfont_get_preset((fluid_ramsfont_t*) sfont->data, bank, prenum);

	if (rampreset == NULL) {
		return NULL;
	}

	preset = FLUID_NEW(fluid_preset_t);
	if (preset == NULL) {
		FLUID_LOG(FLUID_ERR, "Out of memory");
		return NULL;
	}

	preset->sfont = sfont;
	preset->data = rampreset;
	preset->free = fluid_rampreset_preset_delete;
	preset->get_name = fluid_rampreset_preset_get_name;
	preset->get_banknum = fluid_rampreset_preset_get_banknum;
	preset->get_num = fluid_rampreset_preset_get_num;
	preset->noteon = fluid_rampreset_preset_noteon;
	preset->notify = NULL;

	return preset;
}
