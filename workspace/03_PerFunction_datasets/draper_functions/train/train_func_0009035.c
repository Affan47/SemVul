infected_str_new(ptr, len, str)
    const char *ptr;
    long len;
    VALUE str;
{
    VALUE s = rb_str_new(ptr, len);

    OBJ_INFECT(s, str);
    return s;
}
