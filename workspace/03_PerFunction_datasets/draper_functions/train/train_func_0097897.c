xterm_text(int ig1 _is_unused, int ig2 _is_unused)
{
	if (tx < NT)
		text[tx++] = ansi_ch;
	return state;
}
