snumber(cchar *s)
{
    return s && *s && strspn(s, "1234567890") == strlen(s);
}
