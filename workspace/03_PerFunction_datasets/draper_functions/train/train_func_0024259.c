enc_symbol(int number)
{
	int i, j;
	i = j = 0;

	for(j = 15; j >= 0; j--)
	{
		i = number / (1 << j);
		number = number - i * (1 << j);
		fprintf(pOutfile,"%d", i);
		if(settings.code != 0) { printf("%d", i); }
 	}
}
