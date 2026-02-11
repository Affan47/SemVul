readDirective (int c, char *const name, unsigned int maxLength)
{
	unsigned int i;

	for (i = 0  ;  i < maxLength - 1  ;  ++i)
	{
		if (i > 0)
		{
			c = fileGetc ();
			if (c == EOF  ||  ! isalpha (c))
			{
				fileUngetc (c);
				break;
			}
		}
		name [i] = c;
	}
	name [i] = '\0';

	return (boolean) isspacetab (c);
}
