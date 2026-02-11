setFont(const GR_Font * pFont)
{
	UT_return_if_fail( pFont && pFont->getType() == GR_FONT_UNIX_PANGO);


	m_pPFont = const_cast<GR_PangoFont*>(static_cast<const GR_PangoFont*>(pFont));

	_setIsSymbol(false);
	_setIsDingbat(false);

	const char* familyName = m_pPFont->getFamily();

	char * szLCFontName = familyName ? g_utf8_strdown (familyName, -1) : NULL;

	if (szLCFontName)
	{
		xxx_UT_DEBUGMSG(("GR_CairoGraphics::setFont: %s\n", szLCFontName));
		if(strstr(szLCFontName,"symbol") != NULL)
		{


			if(!strstr(szLCFontName,"starsymbol") &&
			   !strstr(szLCFontName,"opensymbol") &&
			   !strstr(szLCFontName,"symbolnerve"))
				_setIsSymbol(true);
		}

		if(strstr(szLCFontName,"dingbat"))
			_setIsDingbat(true);
		FREEP(szLCFontName);
	}

	if(!m_pPFont->isGuiFont() && m_pPFont->getZoom() != getZoomPercentage())
	{
		m_pPFont->reloadFont(this);
	}
}
