FcFontSetSerialize (FcSerialize *serialize, const FcFontSet * s)
{
    int		i;
    FcFontSet	*s_serialize;
    FcPattern	**fonts_serialize;
    FcPattern	*p_serialize;

    s_serialize = FcSerializePtr (serialize, s);
    if (!s_serialize)
	return NULL;
    *s_serialize = *s;
    s_serialize->sfont = s_serialize->nfont;

    fonts_serialize = FcSerializePtr (serialize, s->fonts);
    if (!fonts_serialize)
	return NULL;
    s_serialize->fonts = FcPtrToEncodedOffset (s_serialize,
					       fonts_serialize, FcPattern *);

    for (i = 0; i < s->nfont; i++)
    {
	p_serialize = FcPatternSerialize (serialize, s->fonts[i]);
	if (!p_serialize)
	    return NULL;
	fonts_serialize[i] = FcPtrToEncodedOffset (s_serialize,
						   p_serialize,
						   FcPattern);
    }

    return s_serialize;
}
