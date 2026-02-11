_convertGdkRGBA(const GdkRGBA &c)
{
	UT_RGBColor color;
	color.m_red = c.red * 255;
	color.m_grn = c.green * 255;
	color.m_blu = c.blue * 255;
	return color;
}
