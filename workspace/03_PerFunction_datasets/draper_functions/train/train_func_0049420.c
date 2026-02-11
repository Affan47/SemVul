glyph_name(int gi) const
{

    if (gi == 0)
	return PermString(".notdef");


    if (!_got_glyph_names) {
	OpenType::Post post(_otf->table("post"));
	if (post.ok())
	    post.glyph_names(_glyph_names);
	_got_glyph_names = true;
    }
    if (gi >= 0 && gi < _glyph_names.size())
	return _glyph_names[gi];


    if (!_got_unicodes) {
	OpenType::Cmap cmap(_otf->table("cmap"));
	if (cmap.ok())
	    cmap.unmap_all(_unicodes);

	HashMap<uint32_t, int> unicode_usage(-1);
	for (int g = 0; g < _unicodes.size(); g++)
	    if (_unicodes[g]) {
		int i = unicode_usage.find_force(_unicodes[g], g);
		if (i != g)
		    _unicodes[i] = _unicodes[g] = 0;
	    }
	_got_unicodes = true;
    }

    if (gi >= 0 && gi < _unicodes.size() && _unicodes[gi] > 0 && _unicodes[gi] <= 0xFFFF) {
	char buf[10];
	sprintf(buf, "uni%04X", _unicodes[gi]);
	return PermString(buf);
    } else
	return permprintf("index%d", gi);
}
