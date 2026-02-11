fluid_sample_import_sfont(fluid_sample_t* sample, SFSample* sfsample, fluid_defsfont_t* sfont)
{
	FLUID_STRCPY(sample->name, sfsample->name);
	sample->data = sfont->sampledata;
	sample->start = sfsample->start;
	sample->end = sfsample->start + sfsample->end;
	sample->loopstart = sfsample->start + sfsample->loopstart;
	sample->loopend = sfsample->start + sfsample->loopend;
	sample->samplerate = sfsample->samplerate;
	sample->origpitch = sfsample->origpitch;
	sample->pitchadj = sfsample->pitchadj;
	sample->sampletype = sfsample->sampletype;

	if (sample->sampletype & FLUID_SAMPLETYPE_ROM) {
		sample->valid = 0;
		FLUID_LOG(FLUID_WARN, "Ignoring sample %s: can't use ROM samples", sample->name);
	}
	if (sample->end - sample->start < 8) {
		sample->valid = 0;
		FLUID_LOG(FLUID_WARN, "Ignoring sample %s: too few sample data points", sample->name);
	} else {


	}
	return FLUID_OK;
}
