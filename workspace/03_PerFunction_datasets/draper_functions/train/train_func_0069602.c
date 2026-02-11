superpac_update_credits (void)
{
	int val = readinputport (3) & 0x0f, temp;
	if (val & 1)
	{
		if (!coin1) credits++, coin1++;
	}
	else coin1 = 0;

	if (val & 2)
	{
		if (!coin2) credits++, coin2++;
	}
	else coin2 = 0;

	temp = readinputport (1) & 7;
	val = readinputport (3) >> 4;
	if (val & 1)
	{
		if (!start1 && credits >= credden[temp]) credits -= credden[temp], start1++;
	}
	else start1 = 0;

	if (val & 2)
	{
		if (!start2 && credits >= 2 * credden[temp]) credits -= 2 * credden[temp], start2++;
	}
	else start2 = 0;
}
