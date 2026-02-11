isyes()
{
	int c;
	int fchar;

	fchar = c = getchar();
	while (c != '\n' && c != EOF)
		c = getchar();
	return (fchar == 'y');
}
