gameplay_help_blit_control_line(int x, int y, int id)
{
	int			has_key=0, has_joy=0;
	char			buf[256];
	config_item	*ci;

	ci = &Control_config[id];

	buf[0] = 0;

	if ( ci->key_id >= 0 ) {
		strcpy_s(buf, textify_scancode(ci->key_id));
		has_key=1;
	}

	if ( ci->joy_id >= 0 ) {
		if ( has_key ) {
			strcat_s(buf, XSTR( ", ", 129));
		}
		strcat_s(buf, Joy_button_text[ci->joy_id]);
		has_joy=1;
	}

	if ( !has_key && !has_joy ) {
		strcpy_s(buf, XSTR( "no binding", 130));
	}

	gr_string(x,y,buf);


	gr_string(x+KEY_DESCRIPTION_OFFSET, y, XSTR(ci->text, CONTROL_CONFIG_XSTR + id));
}
