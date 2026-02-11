setutext(const std::string &textArg)
{
	std::vector<unicode_char> buf;

	mail::iconvert::convert(textArg, unicode_default_chset(), buf);

	widecharbuf wc;

	wc.init_unicode(buf.begin(), buf.end());
	wc.expandtabs(0);

	wc.tounicode(utext);
	w=wc.wcwidth(0);
}
