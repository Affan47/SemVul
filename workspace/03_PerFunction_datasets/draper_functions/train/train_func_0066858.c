deflate_run(VALUE args)
{
    struct zstream *z = (struct zstream*)((VALUE*)args)[0];
    VALUE src = ((VALUE*)args)[1];

    zstream_run(z, (Bytef*)RSTRING_PTR(src), RSTRING_LEN(src), Z_FINISH);
    return zstream_detach_buffer(z);
}
