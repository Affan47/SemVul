setTextBeforeAfter(const std::vector<unicode_char> &before,
		     const std::vector<unicode_char> &after,
		     bool flowed)
{
	widecharbuf origline;

	origline.init_unicode(before.begin(), before.end());

	std::vector<unicode_char> newline;

	newline.reserve(before.size()+after.size());

	newline.insert(newline.end(), before.begin(), before.end());
	newline.insert(newline.end(), after.begin(), after.end());

	setText(cursorRow, CursesFlowedLine(newline, flowed));

	cursorCol=origline.wcwidth(0);
}
