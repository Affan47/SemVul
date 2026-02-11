fluid_ramsfont_remove_izone (fluid_ramsfont_t* sfont, unsigned int bank,
                             unsigned int num, fluid_sample_t* sample)
{
	int err;
	fluid_rampreset_t* preset = fluid_ramsfont_get_preset(sfont, bank, num);
	if (preset == NULL) {
		return FLUID_FAILED;
	}


	err = fluid_rampreset_remove_izone(preset, sample);
	if (err != FLUID_OK)
		return err;


	sfont->sample = fluid_list_remove(sfont->sample, sample);

	return FLUID_OK;
}
