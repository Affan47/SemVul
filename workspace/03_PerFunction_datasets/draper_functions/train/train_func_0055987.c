printOptionDescriptions (const optionDescription *const optDesc)
{
	int i;
	for (i = 0 ; optDesc [i].description != NULL ; ++i)
	{
		if (! Option.etags || optDesc [i].usedByEtags)
			puts (optDesc [i].description);
	}
}
