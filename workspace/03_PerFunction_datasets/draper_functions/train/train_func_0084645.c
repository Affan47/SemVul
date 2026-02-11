nextchar(void)
{
	int ch;

	if (depth == 0)
		 return EOF;
	if (cip->i_state == IS_REREAD) {
		 ch = cip->i_char;
		 cip->i_state = IS_READ;
		 if (ch == '\n')
			cip->i_line++;
		 return ch;
	}
	if (cip->i_str) {
		if (cip->i_num) {
			ch = chartoint(*cip->i_cp++);
			cip->i_num--;
		} else {
			ch = EOF;
		}
	} else if (cip->i_fp) {
		ch = fgetc(cip->i_fp);
	} else if (!stdin_tty) {
		ch = fgetc(stdin);
	} else {
		ch = ttychar();
	}
	if (depth > 0)
		cip->i_char = ch;
	if (ch == '\n')
		cip->i_line++;
	return ch;
}
