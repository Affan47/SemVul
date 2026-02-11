rb_gzreader_ungetbyte(VALUE obj, VALUE ch)
{
    struct gzfile *gz = get_gzfile(obj);
    gzfile_ungetbyte(gz, NUM2CHR(ch));
    return Qnil;
}
