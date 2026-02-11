_af_instsetup_new (int instrumentCount)
{
	InstrumentSetup	*instruments;

	if (instrumentCount == 0)
		return NULL;
	instruments = (InstrumentSetup *) _af_calloc(instrumentCount, sizeof (InstrumentSetup));
	if (instruments == NULL)
		return NULL;

	for (int i=0; i<instrumentCount; i++)
	{
		instruments[i] = _af_default_instrumentsetup;
		instruments[i].id = AF_DEFAULT_INST + i;
		if (instruments[i].loopCount == 0)
			instruments[i].loops = NULL;
		else
		{
			instruments[i].loops = (LoopSetup *) _af_calloc(instruments[i].loopCount, sizeof (LoopSetup));
			if (instruments[i].loops == NULL)
				return NULL;

			for (int j=0; j<instruments[i].loopCount; j++)
				instruments[i].loops[j].id = j+1;
		}
	}

	return instruments;
}
