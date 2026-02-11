STRCMP(char *a, char *b)
{
    if (!a || !b)
        if (!a) return strcmp("", b);
	else return strcmp(a, "");
    else return strcmp(a, b);
}
