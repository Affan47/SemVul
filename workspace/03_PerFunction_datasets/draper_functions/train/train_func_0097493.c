validate(string)
	 char            *string;
{
	int             index,
	                count;

	if (string == NULL) {
		return (FALSE);
	}


	count = strlen(string);


	for (index = 0; index < count; index++) {
		if (!isdigit((int) *(string + index)) && string[index] != '-') {

			return (FALSE);
		}
	}

	return (TRUE);
}
