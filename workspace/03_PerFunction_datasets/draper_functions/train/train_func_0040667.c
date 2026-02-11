check(int skill, float score)
{
	int retVal = 0;
	if(skill > 0 && skill < 10)
	{
		int i;
		int rank = -1;
		for(i = HI_SCORE_HIST-1; i >= 0; i--)
		{
			if(score > hiScore[skill][i])
				rank = i;
		}
		if(rank > -1)
		{
			retVal = rank+1;
		}
	}
	return retVal;
}
