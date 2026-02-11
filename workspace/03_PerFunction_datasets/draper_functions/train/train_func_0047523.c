DuplicateString(const char* string)
{
    char* new_string;

    if (string == NUL(char*))
    {
	return NUL(char*);
    }


    new_string = new char[STRLEN(string) + 1];


    strcpy(new_string, string);

    return new_string;
}
