at_cmd_plus_VSID(at_state_t *s, const char *t)
{

    t += 5;
    if (!parse_string_out(s, &t, &s->local_id, NULL))
        return NULL;
    if (at_modem_control(s, AT_MODEM_CONTROL_SETID, s->local_id) < 0)
        return NULL;
    return t;
}
