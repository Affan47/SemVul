get_autoinscription_index(s16b k_idx)
{
	int i;

	for (i = 0; i < inscriptions_count; i++)
	{
		if (k_idx == inscriptions[i].kind_idx)
			return i;
	}

	return -1;
}
