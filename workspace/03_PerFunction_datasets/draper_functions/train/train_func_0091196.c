Append(char **Target, char*Source)
{
	if (*Target == NULL)
	{
		*Target = Source;
		return;
	}

	if (Source == NULL)
		return;

	*Target = (char*) realloc(*Target, sizeof(char)*(strlen(*Target)+strlen(Source)+2));
	strcat(*Target,",");
	strcat(*Target,Source);
}
