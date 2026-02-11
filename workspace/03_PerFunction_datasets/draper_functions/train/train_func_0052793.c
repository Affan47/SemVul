symbolFont(QString const & family, bool * ok)
{
	LYXERR(Debug::FONT, "Looking for font family " << family << " ... ");
	QString upper = family;
	upper[0] = family[0].toUpper();

	QFont font;
	font.setKerning(false);
	font.setFamily(family);

	if (isChosenFont(font, family)) {
		LYXERR(Debug::FONT, "normal!");
		*ok = true;
		return font;
	}

	LYXERR(Debug::FONT, "Trying " << upper << " ... ");
	font.setFamily(upper);

	if (isChosenFont(font, upper)) {
		LYXERR(Debug::FONT, "upper!");
		*ok = true;
		return font;
	}


	QString const raw = rawName(family);
	LYXERR(Debug::FONT, "Trying " << raw << " ... ");
	font.setRawName(raw);

	if (isChosenFont(font, family)) {
		LYXERR(Debug::FONT, "raw version!");
		*ok = true;
		return font;
	}

	LYXERR(Debug::FONT, " FAILED :-(");
	*ok = false;
	return font;
}
