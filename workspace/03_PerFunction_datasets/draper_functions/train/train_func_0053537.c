charmap_table_to_string(int mask, charmap_t *table)
{
	char *allmods;
	int modmask;
	char c[2];

	c[1] = 0;
	modmask = mask;
	allmods = safemalloc(sizeof(table->value) * 8 + 1);
	*allmods = 0;
	for (; table->key !=0; table++)
	{
		c[0] = toupper(table->key);


		if ((modmask & table->value) &&
			(table->value != C_ALL))
		{

			strcat(allmods, c);
			modmask &= ~table->value;
		}
		else if (mask == table->value)
		{

			strcpy(allmods, c);
			break;
		}
	}

	return allmods;
}
