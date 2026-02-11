tty_io_foreground(color)
    int color;
{
    char str[16];

    if (fg_cache == VALID_CACHE && color == TTY_IO_FOREGROUND)
	return;

    if (AnsiColors == ON)
    {
	memcpy(str, ansi_foreground, sizeof(ansi_foreground));
	str[3] += color;
	tty_writes(str, sizeof(ansi_foreground));
    }
    else
	tty_io_reversevid(color != WHITE);

    fg_cache = VALID_CACHE;

    TTY_IO_SET_FOREGROUND(color);
}
