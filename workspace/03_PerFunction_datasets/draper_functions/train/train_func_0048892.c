fluid_voice_update_modenv(fluid_voice_t* voice,
                          fluid_adsr_env_section_t section,
                          unsigned int count,
                          fluid_real_t coeff,
                          fluid_real_t increment,
                          fluid_real_t min,
                          fluid_real_t max)
{
	UPDATE_RVOICE_GENERIC_ALL(fluid_adsr_env_set_data,
	                          &voice->rvoice->envlfo.modenv, section, count,
	                          coeff, increment, min, max);
}
