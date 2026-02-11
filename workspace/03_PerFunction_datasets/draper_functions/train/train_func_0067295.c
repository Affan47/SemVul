cinteger_resolve(name)
	 char            *name;
{
	int             index,
					iterator,
	                counter;
	int             delimiter = 0;
	char            expression[84];

	strncpy(expression, name, 80);

	counter = strlen(expression);

	for (index = 0; index < counter; index++) {
		if (expression[index] == '[') {


			expression[index] = 0;
			delimiter = index + 1;


			for (iterator = counter; iterator > 0; iterator--) {
				if (expression[iterator] == ']') {
					expression[iterator] = 0;
					break;
				} else if (expression[iterator] == '(') {

					return (FALSE);
				}
			}
			break;
		} else if (expression[index] == '<') {


			return (NULL);
		} else if (expression[index] == '(') {


			return (NULL);
		} else if (expression[index] == ' ')
			return (NULL);
	}


	if (delimiter == 0) {
		return (cinteger_resolve_indexed (name, 0));
	}


	if (delimiter == 1) {
		return (NULL);
	}

	counter = value_of(&expression[delimiter], TRUE);

	if (counter > -1) {
		return (cinteger_resolve_indexed (expression, counter));
	} else {

		return (NULL);
	}
}
