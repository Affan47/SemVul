draw_a_cell(int row, int col, int cell_value)
{
    x1 = xoffset + f2s_x * col;
    y1 = yoffset + f2s_y * row;
    x2 = x1 + f2s_x + 0.999;
    y2 = y1 + f2s_y + 0.999;
    D_color(cell_value % 60, &colors);
    R_box_abs(x1, y1, x2, y2);
    R_flush();


    if (cell_value > old_value) {
	old_value = cell_value;
	R_standard_color(9);
	R_box_abs(x1_st + 1, y1_st, x2_st, y2_st - 1);
	R_text_size((int)(0.049 * (x2_st - x1_st)),
		    (int)(0.5 * (y2_st - y1_st)));
	R_move_abs((int)(x1_st + 0.03 * (x2_st - x1_st)),
		   (int)(y1_st + 0.75 * (y2_st - y1_st)));
	R_standard_color(1);
	sprintf(buf, "Elapsed Spread Time %d%d:%d%d", (cell_value / 600),
		(cell_value / 60 - cell_value / 600 * 10),
		((cell_value - cell_value / 60 * 60) / 10),
		((cell_value - cell_value / 60 * 60) -
		 (cell_value - cell_value / 60 * 60) / 10 * 10));
	R_text(buf);

	time(&c_time);
	t_time = localtime(&c_time);
	strftime(cur_time, SIZE, "%H:%M", t_time);
	if (strcmp(cur_time, old_time) != 0) {
	    strcpy(old_time, cur_time);
	    R_standard_color(9);
	    R_box_abs(x1_ct + 1, y1_ct + 1, x2_ct, y2_ct);
	    R_text_size((int)(0.05 * (x2_ct - x1_ct)),
			(int)(0.5 * (y2_ct - y1_ct)));
	    R_move_abs((int)(x1_ct + 0.03 * (x2_ct - x1_ct)),
		       (int)(y1_ct + 0.75 * (y2_ct - y1_ct)));
	    R_standard_color(8);
	    sprintf(buf, "  Current  Time  %s", cur_time);
	    R_text(buf);
	}
    }
}
