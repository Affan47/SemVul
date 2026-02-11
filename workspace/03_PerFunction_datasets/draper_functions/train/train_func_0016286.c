PORT_RegExpValid(const char *exp)
{
    int x;

    x = _valid_subexp(exp, '\0', '\0');
    return (x < 0 ? x : VALID_SXP);
}
