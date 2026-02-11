writeText(const std::vector<unicode_char> &text,
			     int row, int col,
			     const Curses::CursesAttr &attr) const
{
	if (draw_flag)
		CursesContainer::writeText(text, row, col, attr);
	return false;
}
