label_to_inven(int c)
{
	int i;


	i = (islower((unsigned char)c) ? A2I(c) : -1);


	if ((i < 0) || (i > INVEN_PACK)) return (-1);


	if (!inventory[i].k_idx) return (-1);


	return (i);
}
