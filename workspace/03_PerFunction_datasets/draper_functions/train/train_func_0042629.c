setShadingColor(UT_RGBColor clr)
{
	UT_String bgcol = UT_String_sprintf("%02x%02x%02x", clr.m_red, clr.m_grn, clr.m_blu);

	if (clr.isTransparent ())
	{
		m_vecProps.removeProp ("shading-foreground-color");
	}
	else
	{
		m_vecProps.addOrReplaceProp ("shading-foreground-color", bgcol.c_str ());
	}
	m_bSettingsChanged = true;
	UT_DEBUGMSG(("Maleesh ======================= setShadingColor\n"));
}
