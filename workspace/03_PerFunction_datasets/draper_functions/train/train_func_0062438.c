rb_inflate_sync(VALUE obj, VALUE src)
{
    struct zstream *z = get_zstream(obj);

    OBJ_INFECT(obj, src);
    StringValue(src);
    return zstream_sync(z, (Bytef*)RSTRING_PTR(src), RSTRING_LEN(src));
}
