update()
{


	int i;

	wet1 = wet*(width/2 + 0.5f);
	wet2 = wet*((1-width)/2);

	if (mode >= freezemode)
	{
		roomsize1 = 1;
		damp1 = 0;
		gain = muted;
	}
	else
	{
		roomsize1 = roomsize;
		damp1 = damp;
		gain = fixedgain;
	}

	for(i=0; i<numcombs; i++)
	{
		combL[i].setfeedback(roomsize1);
		combR[i].setfeedback(roomsize1);
	}

	for(i=0; i<numcombs; i++)
	{
		combL[i].setdamp(damp1);
		combR[i].setdamp(damp1);
	}
}
