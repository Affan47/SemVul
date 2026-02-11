findNsisTags (void)
{
	vString *name = vStringNew ();
	const unsigned char *line;

	while ((line = fileReadLine ()) != NULL)
	{
		const unsigned char* cp = line;

		while (isspace (*cp))
			cp++;

		if (*cp == '#' || *cp == ';')
			continue;


		if (strncasecmp ((const char*) cp, "function", (size_t) 8) == 0 &&
			isspace ((int) cp [8]))
		{
			cp += 8;

			while (isspace ((int) *cp))
				++cp;
			while (isalnum ((int) *cp) || *cp == '_' || *cp == '-' || *cp == '.' || *cp == '!')
			{
				vStringPut (name, (int) *cp);
				++cp;
			}
			vStringTerminate (name);
			makeSimpleTag (name, NsisKinds, K_FUNCTION);
			vStringClear (name);
		}

		else if (strncasecmp ((const char*) cp, "var", (size_t) 3) == 0 &&
			isspace ((int) cp [3]))
		{
			cp += 3;

			while (isspace ((int) *cp))
				++cp;

			while (*cp == '/')
			{
				++cp;
				while (! isspace ((int) *cp))
					++cp;
				while (isspace ((int) *cp))
					++cp;
			}
			while (isalnum ((int) *cp) || *cp == '_')
			{
				vStringPut (name, (int) *cp);
				++cp;
			}
			vStringTerminate (name);
			makeSimpleTag (name, NsisKinds, K_VARIABLE);
			vStringClear (name);
		}

		else if (strncasecmp ((const char*) cp, "section", (size_t) 7) == 0  &&
				 isspace ((int) cp [7]))
		{
			boolean in_quotes = FALSE;
			cp += 7;

			while (isspace ((int) *cp))
			++cp;
			while (isalnum ((int) *cp) || isspace ((int) *cp) ||
				   *cp == '_' || *cp == '-' || *cp == '.' || *cp == '!' || *cp == '"')
			{
				if (*cp == '"')
				{
					if (in_quotes)
						break;
					else
					{
						in_quotes = TRUE;
						++cp;
						continue;
					}
				}
				vStringPut (name, (int) *cp);
				++cp;
			}
			vStringTerminate (name);
			makeSimpleTag (name, NsisKinds, K_SECTION);
			vStringClear (name);
		}
	}
	vStringDelete (name);
}
