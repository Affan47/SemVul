getStringPart(OFString &result,
                          const char *orgStr,
                          const unsigned long pos)
{
    OFCondition l_error = EC_Normal;

    if (orgStr != NULL)
    {

        unsigned long i = 0;
        while ((i < pos) && (*orgStr != '\0'))
        {
            if (*orgStr++ == '\\')
                i++;
        }

        if (i == pos)
        {

            const char *t = orgStr;
            while ((*t != '\0') && (*t != '\\'))
                t++;

            if (t - orgStr > 0)
                result.assign(orgStr, t - orgStr);
            else
                result = "";
        } else {

            l_error = EC_IllegalParameter;
        }
    } else
        l_error = EC_IllegalParameter;
    return l_error;
}
