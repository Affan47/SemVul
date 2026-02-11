do_math_spacing(Metrics &metrics, const FontInfo &finfo,
		const DvipsEncoding &dvipsenc)
{
    Transform font_xform;
    if (extend)
	font_xform.scale(extend, 1);
    if (slant)
	font_xform.shear(slant);
    CharstringBounds boundser(font_xform);

    int x_height = font_x_height(finfo, font_xform);
    double slant = font_slant(finfo);
    int boundary_char = dvipsenc.boundary_char();

    int bounds[4], width;

    for (int code = 0; code < metrics.encoding_size(); code++)
	if (metrics.was_base_glyph(code) && code != boundary_char
	    && char_bounds(bounds, width, finfo, font_xform, code)) {
	    int left_sb = (bounds[0] < 0 ? -bounds[0] : 0);
	    metrics.add_single_positioning(code, left_sb, 0, left_sb);

	    if (skew_char >= 0 && code < 256) {
		double virtual_height = (bounds[3] > x_height ? bounds[3] :x_height) - 0.5 * x_height;
		int right_sb = (bounds[2] > width ? bounds[2] - width : 0);
		int skew = (int)(slant * virtual_height + left_sb - right_sb);
		metrics.add_kern(code, skew_char, skew);
	    }
	}
}
