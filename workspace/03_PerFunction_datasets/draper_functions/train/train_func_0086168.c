my_isxdigit(char c)
{
    unsigned int uc = c;

    return (uc - '0') < 10 || ((uc | 0x20) - 'a') < 6;
}
