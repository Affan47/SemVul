at_cmd_V(at_state_t *s, const char *t)
{
    int val;


    t += 1;
    if ((val = parse_num(&t, 1)) < 0)
        return NULL;
    s->p.verbose = val;
    if (s->p.result_code_format != NO_RESULT_CODES)
        s->p.result_code_format = (s->p.verbose)  ?  ASCII_RESULT_CODES  :  NUMERIC_RESULT_CODES;
    return t;
}
