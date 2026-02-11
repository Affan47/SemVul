print_hash()
{
	int i = 0;
	printf("---------- HASH TABLE ----------\n");
	printf("Position\tAdd\tName\n");
	while(i < HASH_SIZE)
	{
		if(symbol_hash[i].name[0] != '\0')
		{
			printf("HASH: %d\t%d\t%s\n", i, symbol_hash[i].address, symbol_hash[i].name);
		}
		++i;
	}
}
