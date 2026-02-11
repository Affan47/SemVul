addrinfo_unix_path(VALUE self)
{
    rb_addrinfo_t *rai = get_addrinfo(self);
    int family = ai_get_afamily(rai);
    struct sockaddr_un *addr;
    char *s, *e;

    if (family != AF_UNIX)
	rb_raise(rb_eSocket, "need AF_UNIX address");

    addr = (struct sockaddr_un *)&rai->addr;

    s = addr->sun_path;
    e = (char*)addr + rai->sockaddr_len;
    if (e < s)
        rb_raise(rb_eSocket, "too short AF_UNIX address");
    if (addr->sun_path + sizeof(addr->sun_path) < e)
        rb_raise(rb_eSocket, "too long AF_UNIX address");
    while (s < e && *(e-1) == '\0')
        e--;
    return rb_str_new(s, e-s);
}
