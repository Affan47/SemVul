panel_update_frame(this)
    panel_t *this;
{
    int line;
    tty_status_t status;
    char *buf = xmalloc(this->columns);

    if (!this->visible)
	return;

    tty_save(&status);

    tty_colors(OFF, PanelFrame, PanelFrame);

    for (line = 1; line < this->lines - 1; line++)
    {
	window_goto(this->window, line, 0);
	window_putc(this->window, ' ');
    }

    for (line = 1; line < this->lines - 1; line++)
    {
	window_goto(this->window, line, this->columns - 1);
	window_putc(this->window, ' ');
    }

    memset(buf, ' ', this->columns);
    window_goto(this->window, 0, 0);
    window_puts(this->window, buf, this->columns);
    window_goto(this->window, this->lines - 1, 0);
    window_puts(this->window, buf, this->columns);
    xfree(buf);

    tty_restore(&status);
}
