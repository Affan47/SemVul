krb5int_utf8_isalnum(const char * p)
{
    unsigned c = * (const unsigned char *) p;

    if (!KRB5_ASCII(c))
        return 0;

    return KRB5_ALNUM(c);
}
