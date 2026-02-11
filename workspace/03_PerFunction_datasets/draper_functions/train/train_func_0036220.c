best_hiscore()
{
	if(!hiscores)
		return NULL;

	s_hiscore_t *hs = hiscoretab;
	for(unsigned int i = 1; i < hiscores; ++i)
		if(hiscoretab[i].score > hs->score)
			hs = hiscoretab + i;

	return hs;
}
