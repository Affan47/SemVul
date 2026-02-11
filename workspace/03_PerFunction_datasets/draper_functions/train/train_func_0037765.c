find (char *s)
{
	char *t = s;
	int n = 0;
	int dernier = 0, chiffre = 0, lettre = 0;

	while (isalnum (*t))
	{
		*t = toupper (*t);
		dernier = (isdigit (*t));

		if (isdigit (*t))
			++chiffre;
		else
			++lettre;

		++t;
		++n;
	}
	*t = '\0';

	if (ext_call)
	{


		if ((n < 3) || (n > 6) || (chiffre < 1) || (lettre < 1))
			return (0);
	}
	else
	{


		if ((n < 3) || (n > 6) || (chiffre < 1) || (chiffre > 2) || dernier)
			return (0);
	}

	return (1);
}
