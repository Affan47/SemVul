char_def_alphabet_ext_count(unsigned char *input, int length)
{
	int i, retval = 0;
	for (i = 0; i < length; i++)
		if (char_def_alphabet_ext(input[i]))
			retval++;
	return retval;
}
