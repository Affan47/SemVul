at_cmd_E(at_state_t *s, const char *t)
{
    int val;


    t += 1;
    if ((val = parse_num(&t, 1)) < 0)
        return NULL;
    s->p.echo = val;
    return t;
}
