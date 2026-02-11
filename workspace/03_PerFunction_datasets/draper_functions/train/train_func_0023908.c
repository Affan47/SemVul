fluid_synth_sfunload_callback(void* data, unsigned int msec)
{
	fluid_sfont_info_t *sfont_info = (fluid_sfont_info_t *)data;

	if (delete_fluid_sfont (sfont_info->sfont) == 0) {
		FLUID_FREE (sfont_info);
		FLUID_LOG (FLUID_DBG, "Unloaded SoundFont");
		return FALSE;
	} else return TRUE;
}
