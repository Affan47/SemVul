addrinfo_list_new(VALUE node, VALUE service, VALUE family, VALUE socktype, VALUE protocol, VALUE flags)
{
    VALUE ret;
    struct addrinfo *r;
    VALUE inspectname;

    struct addrinfo *res = call_getaddrinfo(node, service, family, socktype, protocol, flags, 0);

    inspectname = make_inspectname(node, service, res);

    ret = rb_ary_new();
    for (r = res; r; r = r->ai_next) {
        VALUE addr;
        VALUE canonname = Qnil;

        if (r->ai_canonname) {
            canonname = rb_tainted_str_new_cstr(r->ai_canonname);
            OBJ_FREEZE(canonname);
        }

        addr = rsock_addrinfo_new(r->ai_addr, r->ai_addrlen,
                                  r->ai_family, r->ai_socktype, r->ai_protocol,
                                  canonname, inspectname);

        rb_ary_push(ret, addr);
    }

    freeaddrinfo(res);
    return ret;
}
