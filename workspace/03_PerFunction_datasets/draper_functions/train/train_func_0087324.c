vga_putc(int byte)
{
	if (byte == '\n') {
		video_line++;
		video_col = 0;

	} else if (byte == '\r') {
		video_col = 0;

	} else if (byte == '\b') {
		video_col--;

	} else if (byte == '\t') {
		video_col += 4;

	} else if (byte == '\a') {


	} else {
		vidmem[((video_col + (video_line *COLS)) * 2)] = byte;
		vidmem[((video_col + (video_line *COLS)) * 2) +1] = VGA_ATTR_CLR_WHT;
		video_col++;
	}
	if (video_col < 0) {
		video_col = 0;
	}
	if (video_col >= COLS) {
		video_line++;
		video_col = 0;
	}
	if (video_line >= LINES) {
		video_scroll();
		video_line--;
	}

	write_crtc((video_col + (video_line *COLS)) >> 8, CRTC_CURSOR_HI);
	write_crtc((video_col + (video_line *COLS)) & 0x0ff, CRTC_CURSOR_LO);
}
