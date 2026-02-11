argf_readbyte(VALUE argf)
{
    VALUE c;

    NEXT_ARGF_FORWARD(0, 0);
    c = argf_getbyte(argf);
    if (NIL_P(c)) {
	rb_eof_error();
    }
    return c;
}
