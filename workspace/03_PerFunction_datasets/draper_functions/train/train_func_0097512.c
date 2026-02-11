strCaseCompare(const char * s1, const char * s2)
{
    ASSERT(s1 != NULL  &&  s2 != NULL);
    while(1)
    {
        if(tolower(*s1) != tolower(*s2))
        {
            return (int) * s1 - (int) * s2;
        }
        if(*s1 == 0)
        {
            break;
        }
        s1++;
        s2++;
    }
    return 0;
}
