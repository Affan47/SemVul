db_ascii_to_int(char *num_str, unsigned long *int_num)
{
	int i = 0;

	*int_num = 0;
	while (num_str[i])
	{
		if ((num_str[i] >= '0') && (num_str[i] <= '9'))
		{
			*int_num *= 10;
			*int_num += (num_str[i] - '0');
		}
		else
		{
			return -1;
		}
		i++;
	}
	return 0;
}
