charmap_mask_to_char(int mask, charmap_t *table)
{
	char c;

	for (c = 0; table->key != 0; table++)
	{
		if (mask == table->value)
		{
			c = table->key;
			break;
		}
	}

	return c;
}
