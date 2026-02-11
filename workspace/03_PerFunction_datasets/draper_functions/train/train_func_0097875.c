fluid_voice_gen_set(fluid_voice_t* voice, int i, float val)
{
	voice->gen[i].val = val;
	voice->gen[i].flags = GEN_SET;
	if (i == GEN_SAMPLEMODE)
		UPDATE_RVOICE_I1(fluid_rvoice_set_samplemode, (int) val);
}
