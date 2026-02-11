redraw(int y, int back_cursor)
{
	if (y > 0)
		printf(ESC"[%uA", y);
	bb_putchar('\r');
	put_prompt();
	put_till_end_and_adv_cursor();
	printf(SEQ_CLEAR_TILL_END_OF_SCREEN);
	input_backward(back_cursor);
}
