addrinfo_ip_unpack(VALUE self)
{
    rb_addrinfo_t *rai = get_addrinfo(self);
    int family = ai_get_afamily(rai);
    VALUE vflags;
    VALUE ret, portstr;

    if (!IS_IP_FAMILY(family))
	rb_raise(rb_eSocket, "need IPv4 or IPv6 address");

    vflags = INT2NUM(NI_NUMERICHOST|NI_NUMERICSERV);
    ret = addrinfo_getnameinfo(1, &vflags, self);
    portstr = rb_ary_entry(ret, 1);
    rb_ary_store(ret, 1, INT2NUM(atoi(StringValueCStr(portstr))));
    return ret;
}
