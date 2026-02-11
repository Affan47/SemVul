setBorderColorBottom (const UT_RGBColor & clr)
{
	m_borderColorBottom = clr;

	UT_String s = UT_String_sprintf("%02x%02x%02x", clr.m_red, clr.m_grn, clr.m_blu);

	m_vecProps.addOrReplaceProp("bot-color", s.c_str());

	m_bSettingsChanged = true;
}
