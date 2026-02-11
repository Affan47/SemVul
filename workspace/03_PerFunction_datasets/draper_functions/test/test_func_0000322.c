sort_vibration()
{
	gint i;
	gint j;
	gint k;
	VibrationMode mode;

	if(!vibration.geometry) return;
	if(!vibration.modes) return;
	for(i=0;i<vibration.numberOfFrequences-1;i++)
	{
		k = i;
		for(j=i+1;j<vibration.numberOfFrequences;j++)
			if(vibration.modes[j].frequence<vibration.modes[k].frequence) k = j;
		if(k!=i)
		{
			mode = vibration.modes[i];
			vibration.modes[i] = vibration.modes[k];
			vibration.modes[k] = mode;
		}
	}
}
