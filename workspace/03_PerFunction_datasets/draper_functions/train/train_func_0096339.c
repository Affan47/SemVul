makeCompoundFlags(IspellDict *Conf, int affix)
{
	uint32		flag = 0;
	char	   *str = Conf->AffixData[affix];

	while (str && *str)
	{
		flag |= Conf->flagval[*(unsigned char *) str];
		str++;
	}

	return (flag & FF_DICTFLAGMASK);
}
