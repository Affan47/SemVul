at_cmd_I(at_state_t *s, const char *t)
{
    int val;


    t += 1;
    switch (val = parse_num(&t, 255))
    {
    case 0:
        at_put_response(s, model);
        break;
    case 3:
        at_put_response(s, manufacturer);
        break;
    default:
        return NULL;
    }
    return t;
}
