justify_left(CL_GlyphBuffer::Range range, int left)
{
	range.verify(*this);
	std::vector<CL_GlyphBuffer::Range> ranges = get_lines(range);

	for (std::vector<CL_GlyphBuffer::Range>::iterator it = ranges.begin(); it != ranges.end(); ++it)
	{
		CL_GlyphBuffer::Range vis_range = *it;
		CL_Rect line_rect = internal_rect(vis_range);
		int offset = left - line_rect.left;

		for (int glyph = it->start; glyph != it->end; ++glyph)
			glyphs[glyph].pos.x += offset;
	}
}
