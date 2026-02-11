glyph_name(int gid) const
{
    if (gid >= 0 && gid < nglyphs())
	return _cff->sid_permstring(_charset.gid_to_sid(gid));
    else
	return PermString();
}
