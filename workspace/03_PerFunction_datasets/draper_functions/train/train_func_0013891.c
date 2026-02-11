redotoplin(const char *str)
{
	int otoplin = ttyDisplay->toplin;
	home();
	if(*str & 0x80) {


		g_putch((int)*str++);
		ttyDisplay->curx++;
	}
	end_glyphout();
	putsyms(str);
	cl_end();
	ttyDisplay->toplin = 1;
	if(ttyDisplay->cury && otoplin != 3)
		more();
}
