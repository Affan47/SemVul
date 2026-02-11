lstrip(char *c)
{
    while (isspace(*c)) c++;
    return c;
}
