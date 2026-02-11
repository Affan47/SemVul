tty_update()
{
    int pos, x, y;
    int tty_io_cursor_x = -1;
    int tty_io_cursor_y = -1;
    int last_pos = tty_columns * tty_lines;


    if (tty_last_char_flag == OFF)
	last_pos--;


    tty_cursor(OFF);

    for (pos = 0; pos < last_pos; pos++)
	if (tty_scr[pos] != tty_prev_scr[pos] ||
	    tty_atr[pos] != tty_prev_atr[pos])
	{


	    y = pos / tty_columns;
	    x = pos % tty_columns;

	    if (x != tty_io_cursor_x || y != tty_io_cursor_y)
		tty_io_goto(tty_io_cursor_y = y, tty_io_cursor_x = x);


	    tty_io_colors(tty_atr[pos]);
	    tty_writec(tty_scr[pos]);

	    if (++tty_io_cursor_x == tty_columns)
	    {


		tty_io_cursor_x = 0;
		tty_io_cursor_y = -1;
	    }
	}


    tty_io_goto(tty_cursor_y, tty_cursor_x);


    tty_cursor(ON);

    if (tty_index)
	tty_flush();


    memcpy(tty_prev_scr, tty_scr, tty_columns * tty_lines * sizeof(char));
    memcpy(tty_prev_atr, tty_atr, tty_columns * tty_lines * sizeof(char));
}
