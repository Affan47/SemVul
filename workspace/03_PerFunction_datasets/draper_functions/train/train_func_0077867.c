meta_color(unsigned char *s)
{
	if(!strcmp((char *)s,"inverse"))
		return INVERSE;
	else if(!strcmp((char *)s,"underline"))
		return UNDERLINE;
	else if(!strcmp((char *)s,"bold"))
		return BOLD;
	else if(!strcmp((char *)s,"blink"))
		return BLINK;
	else if(!strcmp((char *)s,"dim"))
		return DIM;
	else if(!strcmp((char *)s,"white"))
		return FG_WHITE;
	else if(!strcmp((char *)s,"cyan"))
		return FG_CYAN;
	else if(!strcmp((char *)s,"magenta"))
		return FG_MAGENTA;
	else if(!strcmp((char *)s,"blue"))
		return FG_BLUE;
	else if(!strcmp((char *)s,"yellow"))
		return FG_YELLOW;
	else if(!strcmp((char *)s,"green"))
		return FG_GREEN;
	else if(!strcmp((char *)s,"red"))
		return FG_RED;
	else if(!strcmp((char *)s,"black"))
		return FG_BLACK;
	else if(!strcmp((char *)s,"bg_white"))
		return BG_WHITE;
	else if(!strcmp((char *)s,"bg_cyan"))
		return BG_CYAN;
	else if(!strcmp((char *)s,"bg_magenta"))
		return BG_MAGENTA;
	else if(!strcmp((char *)s,"bg_blue"))
		return BG_BLUE;
	else if(!strcmp((char *)s,"bg_yellow"))
		return BG_YELLOW;
	else if(!strcmp((char *)s,"bg_green"))
		return BG_GREEN;
	else if(!strcmp((char *)s,"bg_red"))
		return BG_RED;
	else if(!strcmp((char *)s,"bg_black"))
		return BG_BLACK;
	else
		return 0;
}
