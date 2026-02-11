SC_MatchString(char **strings)
{
    int i;

    for (i = 0; *strings != NULL; i++)
    {
        if (SC_Compare(*strings++))
        {
            return i;
        }
    }
    return -1;
}
