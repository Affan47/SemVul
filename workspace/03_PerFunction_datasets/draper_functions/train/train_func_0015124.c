check_is_new_line( int &cur_w, int w, int h, int &cur_max_height, int item_idx, int char_idx )
{
	if (cur_max_height < h)
		cur_max_height = h;

	if (cur_w + w > textarea_width  &&  (w < textarea_width || cur_w > 0))
	{
		lines.push_back( OneLineInfo( item_idx, char_idx, cur_max_height ) );

		total_height += cur_max_height + SPACE_BETWEEN_LINES;
		cur_max_height = h;
		cur_w = w;
	} else
	{
		cur_w += w;
	}
}
