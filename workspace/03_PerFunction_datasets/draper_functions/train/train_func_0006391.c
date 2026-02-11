strTrimSurname(char * str, unsigned int initials)
{
    char * in = str;
    char * out = str;
    bool seenComma = false;

    while(*in != 0)
    {
        char ch = *in;
        if(seenComma)
        {
            if(isupper(ch))
            {
                *out++ = ch;
                initials--;
                if(initials == 0)
                {
                    break;
                }
            }
        }
        else
        {
            if(ch == ',')
            {
                seenComma = true;
                if(initials == 0)
                {
                    break;
                }
            }
            *out++ = ch;
        }
        in++;
    }
    *out = 0;
}
