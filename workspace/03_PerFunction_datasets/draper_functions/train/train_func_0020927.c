parse_string_list_out(at_state_t *s, const char **t, int *target, int max_value, const char *prefix, const char *def)
{
    char buf[100];
    int val;
    size_t len;
    char *tmp;

    switch (*(*t)++)
    {
    case '=':
        switch (**t)
        {
        case '?':

            (*t)++;
            snprintf(buf, sizeof(buf), "%s%s", (prefix)  ?  prefix  :  "", def);
            at_put_response(s, buf);
            break;
        default:

            if ((val = match_element(t, def)) < 0)
                return FALSE;
            if (target)
                *target = val;
            break;
        }
        break;
    case '?':

        val = (target)  ?  *target  :  0;
        while (val--  &&  (def = strchr(def, ',')))
            def++;
        if ((tmp = strchr(def, ',')))
            len = tmp - def;
        else
            len = strlen(def);
        snprintf(buf, sizeof(buf), "%s%.*s", (prefix)  ?  prefix  :  "", (int) len, def);
        at_put_response(s, buf);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}
