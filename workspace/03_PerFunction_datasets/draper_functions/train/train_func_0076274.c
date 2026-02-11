validate_enc_binmode(int *fmode_p, int ecflags, rb_encoding *enc, rb_encoding *enc2)
{
    int fmode = *fmode_p;

    if ((fmode & FMODE_READABLE) &&
        !enc2 &&
        !(fmode & FMODE_BINMODE) &&
        !rb_enc_asciicompat(enc ? enc : rb_default_external_encoding()))
        rb_raise(rb_eArgError, "ASCII incompatible encoding needs binmode");

    if (!(fmode & FMODE_BINMODE) &&
	(DEFAULT_TEXTMODE || (ecflags & ECONV_NEWLINE_DECORATOR_MASK))) {
	fmode |= DEFAULT_TEXTMODE;
	*fmode_p = fmode;
    }
#if !DEFAULT_TEXTMODE
    else if (!(ecflags & ECONV_NEWLINE_DECORATOR_MASK)) {
	fmode &= ~FMODE_TEXTMODE;
	*fmode_p = fmode;
    }
#endif
}
