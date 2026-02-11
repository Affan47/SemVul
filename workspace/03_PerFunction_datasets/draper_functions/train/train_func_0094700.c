image_count_options(unsigned int optiontype)
{
	int i;
	unsigned int count = 0;

	for (i = 0; i < cfgn; i++)
		if (image_cfg[i].type == optiontype)
			count++;

	return count;
}
