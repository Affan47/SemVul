IsValidArticleNumber(const char *string)
{
    int len = 0;
    const unsigned char *p;


    if (string == NULL)
        return false;

    p = (const unsigned char *) string;

    for (; *p != '\0'; p++) {
        len++;
        if (!isdigit((unsigned char) *p))
            return false;
    }

    if (len > 0 && len < 17)
        return true;
    else
        return false;
}
