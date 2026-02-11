send_attr(uint16_t fg, uint16_t bg)
{
#define LAST_ATTR_INIT 0xFFFF
	static uint16_t lastfg = LAST_ATTR_INIT, lastbg = LAST_ATTR_INIT;
	if (fg != lastfg || bg != lastbg) {
		fputs(funcs[T_SGR0], out);

		fprintf(out, funcs[T_SGR], fg & 0x0F, bg & 0x0F);
		if (fg & TB_BOLD)
			fputs(funcs[T_BOLD], out);
		if (bg & TB_BOLD)
			fputs(funcs[T_BLINK], out);
		if (fg & TB_UNDERLINE)
			fputs(funcs[T_UNDERLINE], out);

		lastfg = fg;
		lastbg = bg;
	}
}
