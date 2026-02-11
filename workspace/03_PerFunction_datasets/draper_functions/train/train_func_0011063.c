cdiff_token(const char *line, unsigned int token, unsigned int last)
{
	unsigned int counter = 0, i, j;
	char *buffer;


    for(i = 0; line[i] && counter != token; i++)
	if(line[i] == ' ')
	    counter++;

    if(!line[i])
	return NULL;

    if(last)
	return strdup(&line[i]);

    for(j = i; line[j]; j++)
	if(line[j] == ' ')
	    break;

    if(i == j)
	return NULL;

    buffer = malloc(j - i + 1);
    if(!buffer)
	return NULL;

    strncpy(buffer, line + i, j - i);
    buffer[j - i] = '\0';

    return buffer;
}
