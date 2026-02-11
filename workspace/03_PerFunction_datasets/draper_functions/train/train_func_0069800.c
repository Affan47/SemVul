hostToDicomFilename(char *fname)
{


    size_t len = strlen(fname);
    int k = 0;
    unsigned char c = '\0';
    for (size_t i = 0; i < len; ++i)
    {
        c = OFstatic_cast(unsigned char, fname[i]);

        if (c == PATH_SEPARATOR)
        {
            fname[k++] = '\\';
        } else if (isalpha(c) || isdigit(c) || (c == '_') || (c == '\\')) {

            fname[k++] = OFstatic_cast(char, toupper(c));
        }
    }
    fname[k] = '\0';
}
