csr1212_check_keyword(const char *s)
{
	for (; *s; s++) {

		if (('A' <= *s) && (*s <= 'Z'))
			continue;
		if (('0' <= *s) && (*s <= '9'))
			continue;
		if (*s == '-')
			continue;

		return -1;
	}


	return CSR1212_SUCCESS;
}
