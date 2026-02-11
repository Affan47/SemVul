parseIdentifier (vString *const string, const int firstChar)
{
	int c = firstChar;

	do
	{
		vStringPut (string, c);
		c = fileGetc ();
	} while (isident (c));

	vStringTerminate (string);
	if (!isspace (c))
		fileUngetc (c);
}
