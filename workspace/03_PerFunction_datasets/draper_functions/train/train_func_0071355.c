sock_s_unpack_sockaddr_un(VALUE self, VALUE addr)
{
    struct sockaddr_un * sockaddr;
    VALUE path;

    sockaddr = (struct sockaddr_un*)SockAddrStringValuePtr(addr);
    if (RSTRING_LEN(addr) <
        (char*)&((struct sockaddr *)sockaddr)->sa_family +
        sizeof(((struct sockaddr *)sockaddr)->sa_family) -
        (char*)sockaddr)
        rb_raise(rb_eArgError, "too short sockaddr");
    if (((struct sockaddr *)sockaddr)->sa_family != AF_UNIX) {
        rb_raise(rb_eArgError, "not an AF_UNIX sockaddr");
    }
    if (sizeof(struct sockaddr_un) < (size_t)RSTRING_LEN(addr)) {
	rb_raise(rb_eTypeError, "too long sockaddr_un - %ld longer than %d",
		 RSTRING_LEN(addr), (int)sizeof(struct sockaddr_un));
    }
    path = rsock_unixpath_str(sockaddr, RSTRING_LENINT(addr));
    OBJ_INFECT(path, addr);
    return path;
}
