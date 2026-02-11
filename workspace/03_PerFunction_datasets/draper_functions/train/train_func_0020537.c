vty_ensure(vty_t *vty, int length)
{
	if (vty->max <= length) {
		vty->max *= 2;
		vty->buf = REALLOC(vty->buf, vty->max);
	}
}
