rb_enc_path_next(const char *s, const char *e, rb_encoding *enc)
{
    while (s < e && !isdirsep(*s)) {
	Inc(s, e, enc);
    }
    return (char *)s;
}
