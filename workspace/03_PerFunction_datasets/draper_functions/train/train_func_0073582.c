is_linebreak(int idx, const CL_Font& fnt) const
{
	const unsigned int chr = glyphs[idx].character;


	if (

	idx == static_cast<int>(glyphs.size()-1) ||

	chr == '\n' ||

	glyphs[idx+1].pos.x < glyphs[idx].pos.x + fnt.get_width(chr)
	)
		return true;

	return false;
}
