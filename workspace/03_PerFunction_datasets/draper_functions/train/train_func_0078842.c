verticalLine(int x, int y, int n, char_type c)
{
	for (int i = 0; i < n && i + y < ymax_; ++i)
		at(x, y + i) = c;
}
