AdjustPop(int adjustment)
{
	if(!town) {
		population += adjustment;
		return;
	}

	int tspace = town->hab - town->pop;
	int rspace = habitat - population;
	town->pop += adjustment * tspace / (tspace + rspace);
	if(town->pop < 0) town->pop = 0;
	population += adjustment * rspace / (tspace + rspace);
	if (population < 0) population = 0;
}
