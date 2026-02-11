scroll_to_the_end()
{
	if (pars.size() == 0  ||  total_lines_count == 0)
		return;

	const int SOME_RESERVED_SPACE = 5;

	int was_draw_from = draw_from;
	draw_from = total_lines_count - 1;

	int used_height = get_line(draw_from)->height + CL_RichEdit_Paragraph::SPACE_BETWEEN_LINES;
	int height = richedit->get_height() - bounds_height - CL_RichEdit_Paragraph::SPACE_BETWEEN_LINES * 2;


	while ( draw_from > 0 )
	{
		draw_from --;
		int h = get_line(draw_from)->height + CL_RichEdit_Paragraph::SPACE_BETWEEN_LINES;
		if (used_height + h >= height - SOME_RESERVED_SPACE)
			break;
		used_height += h;
	}

	if (draw_from != was_draw_from)
		sig_draw_from_changed();
}
