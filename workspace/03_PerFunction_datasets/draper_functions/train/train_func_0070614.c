strContainsIndex(const char * longStr, const char * keyStr)
{
    int index = 0;
    while(*longStr)
    {
        if(strIsPrefix(keyStr, longStr))
        {
            return index;
        }
        longStr++;
        index++;
    }
    return -1;
}
