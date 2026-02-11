rb_gzwriter_write(VALUE obj, VALUE str)
{
    struct gzfile *gz = get_gzfile(obj);

    if (TYPE(str) != T_STRING)
	str = rb_obj_as_string(str);
    if (gz->enc2 && gz->enc2 != rb_ascii8bit_encoding()) {
	str = rb_str_conv_enc(str, rb_enc_get(str), gz->enc2);
    }
    gzfile_write(gz, (Bytef*)RSTRING_PTR(str), RSTRING_LEN(str));
    return INT2FIX(RSTRING_LEN(str));
}
