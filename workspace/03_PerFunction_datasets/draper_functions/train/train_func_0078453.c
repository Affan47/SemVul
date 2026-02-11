Hal_GetChnlGroup(u8 chnl)
{
	u8 group = 0;

	if (chnl < 3)
		group = 0;
	else if (chnl < 9)
		group = 1;
	else
		group = 2;

	return group;
}
