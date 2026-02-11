colorize(char* string, int color) {
	if(render_with_colors) {
		sprintf(colorized, "%c[0;30;%dm%s%c[0m", 0x1B, color, string, 0x1B);
		return colorized;
	}

	return string;
}
