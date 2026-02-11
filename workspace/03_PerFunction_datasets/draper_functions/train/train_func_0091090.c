parse_number(const wcstring &arg, long long *out)
{
    const wchar_t *str = arg.c_str();
    wchar_t *endptr = NULL;
    *out = wcstoll(str, &endptr, 10);
    return endptr && *endptr == L'\0';
}
