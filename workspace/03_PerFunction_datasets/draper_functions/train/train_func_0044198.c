gdi_get_color_32bpp(HGDI_DC hdc, GDI_COLOR color)
{
	uint32 color32;
	uint8 a, r, g, b;

	a = 0xFF;
	GetRGB32(r, g, b, color);

	if (hdc->invert)
	{
		color32 = ABGR32(a, r, g, b);
	}
	else
	{
		color32 = ARGB32(a, r, g, b);
	}

	return color32;
}
