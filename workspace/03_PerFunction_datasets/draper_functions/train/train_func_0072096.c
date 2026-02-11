index_to_value (const gint *value_map,
                gint index)
{
	gint i;


	for (i = 0; value_map[i] != -1; i++)
		if (i == index)
			return value_map[i];

	return -1;
}
