addrinfo_ip_p(VALUE self)
{
    rb_addrinfo_t *rai = get_addrinfo(self);
    int family = ai_get_afamily(rai);
    return IS_IP_FAMILY(family) ? Qtrue : Qfalse;
}
