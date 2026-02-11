wsp_pack_integer_string(Octstr *packed, Octstr *value)
{
    unsigned long integer;
    long pos;
    int c;
    int digit;

    integer = 0;
    for (pos = 0; pos < octstr_len(value); pos++) {
        c = octstr_get_char(value, pos);
        if (!isdigit(c))
            break;
        digit = c - '0';
        if (integer > ULONG_MAX / 10)
            goto overflow;
        integer *= 10;
        if (integer > ULONG_MAX - digit)
            goto overflow;
        integer += digit;
    }

    wsp_pack_integer_value(packed, integer);
    return 0;

overflow:
    warning(0, "WSP: Number too large to handle: '%s'.",
            octstr_get_cstr(value));
    return -1;
}
