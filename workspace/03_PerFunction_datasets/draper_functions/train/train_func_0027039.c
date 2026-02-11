mtree_atol10(char **p)
{
    int64_t l, limit, last_digit_limit;
    int base, digit, sign;

    base = 10;
    limit = INT64_MAX / base;
    last_digit_limit = INT64_MAX % base;

    if (**p == '-') {
        sign = -1;
        ++(*p);
    } else
        sign = 1;

    l = 0;
    digit = **p - '0';
    while (digit >= 0 && digit < base) {
        if (l > limit || (l == limit && digit > last_digit_limit)) {
            l = INT64_MAX;
            break;
        }
        l = (l * base) + digit;
        digit = *++(*p) - '0';
    }
    return (sign < 0) ? -l : l;
}
