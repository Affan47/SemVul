tb_set_cursor(int cx, int cy)
{
	if (IS_CURSOR_HIDDEN(cursor_x, cursor_y) && !IS_CURSOR_HIDDEN(cx, cy))
		fputs(funcs[T_SHOW_CURSOR], out);

	if (!IS_CURSOR_HIDDEN(cursor_x, cursor_y) && IS_CURSOR_HIDDEN(cx, cy))
		fputs(funcs[T_HIDE_CURSOR], out);

	cursor_x = cx;
	cursor_y = cy;
	if (!IS_CURSOR_HIDDEN(cursor_x, cursor_y))
		fprintf(out, funcs[T_MOVE_CURSOR], cursor_y+1, cursor_x+1);
}
