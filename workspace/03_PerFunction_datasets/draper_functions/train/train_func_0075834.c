malook(const char *name, struct macro *data, struct macro **table)
{
	struct macro	*mp;
	unsigned	h;

	mp = table[h = mahash(name)];
	while (mp != NULL) {
		if (mp->ma_name && strcmp(mp->ma_name, name) == 0)
			break;
		mp = mp->ma_next;
	}
	if (data) {
		if (mp != NULL)
			return mp;
		data->ma_next = table[h];
		table[h] = data;
	}
	return mp;
}
