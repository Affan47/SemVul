growString (vstring *s)
{
    int result = 0;
    size_t newLength;
    char *newLine;
    if (s->size == 0)
    {
	newLength = 128;
	newLine = (char*) malloc (newLength);
	*newLine = '\0';
    }
    else
    {
	newLength = 2 * s->size;
	newLine = (char*) realloc (s->buffer, newLength);
    }
    if (newLine == NULL)
	perror ("string too large");
    else
    {
	s->buffer = newLine;
	s->size = newLength;
	result = 1;
    }
    return result;
}
