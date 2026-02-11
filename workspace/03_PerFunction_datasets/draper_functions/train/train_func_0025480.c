CreateNewTheme (Theme *theme)
{
	gchar *name = g_strdup (_("NewTheme1"));
	int i = 2;
	while (m_Themes[name] != NULL) {
		g_free (name);
		name = g_strdup_printf (_("NewTheme%d"), i++);
	}
	Theme *pTheme = new Theme (name);
	m_Themes[name] = pTheme;
	m_Names.push_back (name);
	g_free (name);
	if (theme) {
		pTheme->m_ZoomFactor = theme->m_ZoomFactor;
		pTheme->m_BondLength = theme->m_BondLength;
		pTheme->m_BondAngle = theme->m_BondAngle;
		pTheme->m_BondDist = theme->m_BondDist;
		pTheme->m_BondWidth = theme->m_BondWidth;
		pTheme->m_ArrowLength = theme->m_ArrowLength;
		pTheme->m_HashWidth = theme->m_HashWidth;
		pTheme->m_HashDist = theme->m_HashDist;
		pTheme->m_StereoBondWidth = theme->m_StereoBondWidth;
		pTheme->m_Padding = theme->m_Padding;
		pTheme->m_ArrowHeadA = theme->m_ArrowHeadA;
		pTheme->m_ArrowHeadB = theme->m_ArrowHeadB;
		pTheme->m_ArrowHeadC = theme->m_ArrowHeadC;
		pTheme->m_ArrowDist = theme->m_ArrowDist;
		pTheme->m_ArrowPadding = theme->m_ArrowPadding;
		pTheme->m_ArrowWidth = theme->m_ArrowWidth;
		pTheme->m_StoichiometryPadding = theme->m_StoichiometryPadding;
		pTheme->m_ObjectPadding = theme->m_ObjectPadding;
		pTheme->m_SignPadding = theme->m_SignPadding;
		pTheme->m_ChargeSignSize = theme->m_ChargeSignSize;
		g_free (pTheme->m_FontFamily);
		pTheme->m_FontFamily = strdup (theme->m_FontFamily);
		pTheme->m_FontStyle = theme->m_FontStyle;
		pTheme->m_FontWeight = theme->m_FontWeight;
		pTheme->m_FontVariant = theme->m_FontVariant;
		pTheme->m_FontStretch = theme->m_FontStretch;
		pTheme->m_FontSize = theme->m_FontSize;
		g_free (pTheme->m_TextFontFamily);
		pTheme->m_TextFontFamily = strdup (theme->m_TextFontFamily);
		pTheme->m_TextFontStyle = theme->m_TextFontStyle;
		pTheme->m_TextFontWeight = theme->m_TextFontWeight;
		pTheme->m_TextFontVariant = theme->m_TextFontVariant;
		pTheme->m_TextFontStretch = theme->m_TextFontStretch;
		pTheme->m_TextFontSize = theme->m_TextFontSize;
	}
	pTheme->m_ThemeType = LOCAL_THEME_TYPE;
	pTheme->modified = true;
	return pTheme;
}
