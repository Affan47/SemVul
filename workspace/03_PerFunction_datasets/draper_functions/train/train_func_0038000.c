checkForValidUIDFormat(const OFString &stringValue)
{
    OFBool result = OFFalse;

    if (!stringValue.empty())
    {
        const unsigned char *p = OFreinterpret_cast(const unsigned char *, stringValue.c_str());
        if (p != NULL)
        {

            while (isdigit(*p))
            {
                result = OFTrue;
                p++;
            }

            while ((*p == '.') && result)
            {

                result = OFFalse;
                p++;

                while (isdigit(*p))
                {
                    result = OFTrue;
                    p++;
                }
            }

            if (*p != 0)
                result = OFFalse;
        }
    }
    return result;
}
