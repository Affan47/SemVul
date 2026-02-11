textwidth(const char *txt, int min, int max)
{
	if(!engine)
		return strlen(txt);

	SoFont *f = engine->get_font(_font);
	if(!f)
		return strlen(txt);

	return (f->TextWidth(txt, min, max) << 8) / xs;
}
