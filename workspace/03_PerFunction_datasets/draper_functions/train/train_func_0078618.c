jim_strtol(const char *str, char **endptr)
{
    int sign;
    int base;
    int i = JimNumberBase(str, &base, &sign);

    if (base != 10) {
        long value = strtol(str + i, endptr, base);
        if (endptr == NULL || *endptr != str + i) {
            return value * sign;
        }
    }


    return strtol(str, endptr, 10);
}
