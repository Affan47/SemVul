W_LumpNameHash(const char *s)
{


    unsigned int result = 5381;
    unsigned int i;

    for (i=0; i < 8 && s[i] != '\0'; ++i)
    {
        result = ((result << 5) ^ result ) ^ toupper(s[i]);
    }

    return result;
}
