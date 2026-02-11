getStringPart(OFString &result,
                          const char *str,
                          const unsigned long len,
                          const unsigned long pos)
{
    OFCondition l_error = EC_Normal;

    if (str != NULL)
    {

        unsigned long i = 0;
        unsigned long curPos = 0;
        while ((curPos < pos) && (i++ < len))
        {
            if (*str++ == '\\')
                curPos++;
        }

        if (curPos == pos)
        {

            const char *p = str;
            while ((*p != '\\') && (i++ < len))
                p++;

            if (p - str > 0)
                result.assign(str, p - str);
            else
                result.clear();
        } else {

            l_error = EC_IllegalParameter;
        }
    } else
        l_error = EC_IllegalParameter;
    return l_error;
}
