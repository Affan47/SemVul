glyphid(PermString name) const
{
    if (cff)
	return cff->glyphid(name);
    else {
	if (!_got_glyph_names) {
	    glyph_names(_glyph_names);
	    _got_glyph_names = true;
	}
	PermString *found = std::find(_glyph_names.begin(), _glyph_names.end(), name);
	if (found == _glyph_names.end())
	    return 0;
	return found - _glyph_names.begin();
    }
}
