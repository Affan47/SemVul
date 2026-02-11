symbolFamily(FontFamily family)
{
	for (size_t i = 0; i < nr_symbol_fonts; ++i) {
		if (family == symbol_fonts[i].lyx_family)
			return symbol_fonts[i].family;
	}
	return QString();
}
