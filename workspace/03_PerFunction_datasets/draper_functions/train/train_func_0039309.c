bitstr_parse_export(char *exp, const char *s)
{
    bitstr_t x;
    if( bitstr_parse(x, s) != -1 ){
        bitstr_export(exp, x);
        return 0;
    }
    return -1;
}
