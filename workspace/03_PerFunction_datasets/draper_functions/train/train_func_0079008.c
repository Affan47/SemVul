inspect_socktype(int level, int optname, VALUE data, VALUE ret)
{
    if (RSTRING_LEN(data) == sizeof(int)) {
        int i;
        ID id;
        memcpy((char*)&i, RSTRING_PTR(data), sizeof(int));
        id = rsock_intern_socktype(i);
        if (id)
            rb_str_catf(ret, " %s", rb_id2name(id));
        else
            rb_str_catf(ret, " %d", i);
        return 1;
    }
    else {
        return 0;
    }
}
