update_cursor_pos(void)
{
	struct {
		unsigned char lines, cols, x, y;
	} screen;

	if (vcsa_fd < 0)
		return 0;
	if (lseek(vcsa_fd, 0, SEEK_SET) == -1)
		return 0;
	if (read(vcsa_fd, &screen, sizeof(screen)) == -1)
		return 0;
	cur_x = screen.x+1;
	cur_y = screen.y+1;
	return 1;
}
