read(uint &rawchar, vcp &color, int x, int y) const
{
	if (!buf) return false;
	if ((x >= w) || (y >= h)) return false;
	ColoredChar *b = buf + x + y*w;
	rawchar = b->rawchar;
	color = b->color;
	return true;
}
