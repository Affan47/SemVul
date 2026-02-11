krb5int_utf8_isspace(const char * p)
{
    unsigned c = * (const unsigned char *) p;

    if (!KRB5_ASCII(c))
        return 0;

    switch(c) {
    case ' ':
    case '\t':
    case '\n':
    case '\r':
    case '\v':
    case '\f':
        return 1;
    }

    return 0;
}
