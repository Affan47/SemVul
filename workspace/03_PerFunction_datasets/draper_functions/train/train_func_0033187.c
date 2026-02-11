skipWhitespace (const unsigned char** cp)
{
	while (isspace (**cp))
	{
	    ++*cp;
	}
}
