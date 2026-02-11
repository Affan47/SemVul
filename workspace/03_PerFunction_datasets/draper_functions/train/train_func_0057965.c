restart_header (void)
{
    zword screen_x_size;
    zword screen_y_size;
    zbyte font_x_size;
    zbyte font_y_size;

    int i;

    SET_BYTE (H_CONFIG, h_config)
    SET_WORD (H_FLAGS, h_flags)

    if (h_version >= V4) {
	SET_BYTE (H_INTERPRETER_NUMBER, h_interpreter_number)
	SET_BYTE (H_INTERPRETER_VERSION, h_interpreter_version)
	SET_BYTE (H_SCREEN_ROWS, h_screen_rows)
	SET_BYTE (H_SCREEN_COLS, h_screen_cols)
    }


    if (h_version != V6) {
	screen_x_size = (zword) h_screen_cols;
	screen_y_size = (zword) h_screen_rows;
	font_x_size = 1;
	font_y_size = 1;
    } else {
	screen_x_size = h_screen_width;
	screen_y_size = h_screen_height;
	font_x_size = h_font_width;
	font_y_size = h_font_height;
    }

    if (h_version >= V5) {
	SET_WORD (H_SCREEN_WIDTH, screen_x_size)
	SET_WORD (H_SCREEN_HEIGHT, screen_y_size)
	SET_BYTE (H_FONT_HEIGHT, font_y_size)
	SET_BYTE (H_FONT_WIDTH, font_x_size)
	SET_BYTE (H_DEFAULT_BACKGROUND, h_default_background)
	SET_BYTE (H_DEFAULT_FOREGROUND, h_default_foreground)
    }

    if (h_version == V6)
	for (i = 0; i < 8; i++)
	    storeb ((zword) (H_USER_NAME + i), h_user_name[i]);

    SET_BYTE (H_STANDARD_HIGH, h_standard_high)
    SET_BYTE (H_STANDARD_LOW, h_standard_low)

}
