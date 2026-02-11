data_is_one_string(struct data d)
{
	int i;
	int len = d.len;

	if (len == 0)
		return false;

	for (i = 0; i < len-1; i++)
		if (d.val[i] == '\0')
			return false;

	if (d.val[len-1] != '\0')
		return false;

	return true;
}
