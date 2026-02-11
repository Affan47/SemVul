augmentFont(FontInfo & font, docstring const & name)
{
	static bool initialized = false;
	if (!initialized) {
		initialized = true;

		if (!theFontLoader().available(getFont(from_ascii("mathfrak"))))
			fakeFont(from_ascii("mathfrak"), from_ascii("lyxfakefrak"));
		if (!theFontLoader().available(getFont(from_ascii("mathcal"))))
			fakeFont(from_ascii("mathcal"), from_ascii("lyxfakecal"));
	}
	fontinfo * info = searchFont(name);
	if (info->family_ != inh_family)
		font.setFamily(info->family_);
	if (info->series_ != inh_series)
		font.setSeries(info->series_);
	if (info->shape_ != inh_shape)
		font.setShape(info->shape_);
	if (info->color_ != Color_none)
		font.setColor(info->color_);
}
