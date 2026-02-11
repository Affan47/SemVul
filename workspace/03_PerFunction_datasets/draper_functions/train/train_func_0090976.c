tty_end(EditLine *el)
{
	if (tty_setty(el, TCSAFLUSH, &el->el_tty.t_or) == -1) {
#ifdef DEBUG_TTY
		(void) fprintf(el->el_errfile,
		    "%s: tty_setty: %s\n", __func__, strerror(errno));
#endif
	}
}
