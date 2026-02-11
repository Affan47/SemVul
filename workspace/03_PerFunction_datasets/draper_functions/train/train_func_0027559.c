int_to_roman(int n, char *roman, size_t bufsize)
{

	char roman_symbol_labels[13][3] =
		{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX",
		 "V", "IV", "I"};
	int  roman_symbol_values[13] =
		{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};


	roman[0] = '\0';


	if (n < 1)
		return 0;


	while (n > 0)
	{
		int i = 0;


		while (n < roman_symbol_values[i])
			i++;


		if (strlen(roman) + strlen(roman_symbol_labels[i]) + 1
			> bufsize)
			break;


		my_strcat(roman, roman_symbol_labels[i], bufsize);


		n -= roman_symbol_values[i];
	}


	if (n > 0)
	{

		roman[0] = '\0';

		return 0;
	}

	return 1;
}
