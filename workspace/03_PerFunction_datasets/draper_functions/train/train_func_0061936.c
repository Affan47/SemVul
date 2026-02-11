check_pipe_command(VALUE filename_or_command)
{
    char *s = RSTRING_PTR(filename_or_command);
    long l = RSTRING_LEN(filename_or_command);
    char *e = s + l;
    int chlen;

    if (rb_enc_ascget(s, e, &chlen, rb_enc_get(filename_or_command)) == '|') {
        VALUE cmd = rb_str_new(s+chlen, l-chlen);
        OBJ_INFECT(cmd, filename_or_command);
        return cmd;
    }
    return Qnil;
}
