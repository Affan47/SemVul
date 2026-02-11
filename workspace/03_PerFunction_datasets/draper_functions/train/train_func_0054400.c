openpfile(void)
{
	int	i;


	for  (i = 0;  i < SPP_NSTATES;  i++)
		statenames[i] = gprompt(200+i);
}
