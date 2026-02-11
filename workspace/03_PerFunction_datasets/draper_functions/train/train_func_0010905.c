extract_binmode(VALUE opthash, int *fmode)
{
    if (!NIL_P(opthash)) {
	VALUE v;
	v = rb_hash_aref(opthash, sym_textmode);
	if (!NIL_P(v) && RTEST(v))
            *fmode |= FMODE_TEXTMODE;
	v = rb_hash_aref(opthash, sym_binmode);
	if (!NIL_P(v) && RTEST(v))
            *fmode |= FMODE_BINMODE;

	if ((*fmode & FMODE_BINMODE) && (*fmode & FMODE_TEXTMODE))
	    rb_raise(rb_eArgError, "both textmode and binmode specified");
    }
}
