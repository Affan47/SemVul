containsExtendedCharacters(const OFBool )
{
    char *str = NULL;
    Uint32 len = 0;

    if (getString(str, len).good() && (str != NULL))
    {
        const char *p = str;
        for (Uint32 i = 0; i < len; i++)
        {

            if (OFstatic_cast(unsigned char, *p++) > 127)
                return OFTrue;
        }
    }
    return OFFalse;
}
