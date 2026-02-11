setText(size_t line,
				const std::vector<unicode_char> &textRef)
{
	if (line >= numLines())
		abort();

	text_UTF8[line]=CursesFlowedLine(textRef, false);
}
