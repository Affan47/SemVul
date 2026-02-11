SetMode()
{
	InputIterator = Inputs.begin();
	HaveInput = 0;

	if (MachineWantsChannels > 1)
	{
		numChannels = MachineWantsChannels;
		pmi->pCB->SetnumOutputChannels(ThisMachine, numChannels);
		pmi->OutputModeChanged(numChannels > 1 ? true : false);
		return;
	}


	for (InputList::iterator i = Inputs.begin(); i != Inputs.end(); i++)
	{
		if ((*i).Stereo)
		{
			numChannels = 2;
			pmi->pCB->SetnumOutputChannels(ThisMachine, numChannels);
			pmi->OutputModeChanged(numChannels > 1 ? true : false);
			return;
		}
	}

	numChannels = 1;
	pmi->pCB->SetnumOutputChannels(ThisMachine, numChannels);
	pmi->OutputModeChanged(numChannels > 1 ? true : false);

}
