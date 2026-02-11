cx_edit_insert_spc(void)
{
	int v1, v2, v3, val;
	int ch;

	ch = kbd_getraw();


	if ((v1 = conv_dec(ch)) >= 0) {
		v2 = conv_dec(kbd_getraw());
		v3 = conv_dec(kbd_getraw());
		val = 100 * v1 + 10 * v2 + v3;
		if (v1 >= 0 && v2 >= 0 && v3 >= 0 && val > 0 && val < 256)
			edit_insertchar(val);
		else
			win_remark("usage: ctrl-V N N N, "
			  "where NNN is decimal ASCII code (001 to 255)");
		return;
	}


	if (ch == 'x' || ch == 'X') {
		v1 = conv_hex(kbd_getraw());
		v2 = conv_hex(kbd_getraw());
		val = 16 * v1 + v2;
		if (v1 >= 0 && v2 >= 0 && val > 0)
			edit_insertchar(val);
		else
			win_remark("usage: ctrl-V x H H, "
			  "where HH is hex ASCII code (01 to FF)");
		return;
	}


	if (IS_CHAR(ch)) {
		if (ch != '\0')
			edit_insertchar(ch);
	}
	else
		win_remark("function key codes cannot be inserted");
}
