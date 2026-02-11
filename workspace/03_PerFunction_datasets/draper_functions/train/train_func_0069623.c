landmark(ErrorHandler *errh) const
{
    if (_cur_glyph >= 0 && _cur_glyph < program()->nglyphs())
	return errh->format("glyph %<%s%>", program()->glyph_name(_cur_glyph).c_str());
    else
	return String();
}
