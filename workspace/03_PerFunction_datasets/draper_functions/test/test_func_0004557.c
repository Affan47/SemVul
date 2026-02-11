term_overwrite(EditLine *el, const Char *cp, size_t n)
{
	if (n == 0)
		return;

	if (n > (size_t)el->el_term.t_size.h) {
#ifdef DEBUG_SCREEN
		(void) fprintf(el->el_errfile,
		    "term_overwrite: n is riduculous: %d\r\n", n);
#endif
		return;
	}

        do {

                term__putc(el, *cp++);
                el->el_cursor.h++;
        } while (--n);

	if (el->el_cursor.h >= el->el_term.t_size.h) {
		if (EL_HAS_AUTO_MARGINS) {
			el->el_cursor.h = 0;
			el->el_cursor.v++;
			if (EL_HAS_MAGIC_MARGINS) {


				Char c;
				if ((c = el->el_display[el->el_cursor.v]
				    [el->el_cursor.h]) != '\0') {
					term_overwrite(el, &c, 1);
#ifdef WIDECHAR
					while (el->el_display[el->el_cursor.v]
					    [el->el_cursor.h] == MB_FILL_CHAR)
						el->el_cursor.h++;
#endif
				} else {
					term__putc(el, ' ');
					el->el_cursor.h = 1;
				}
			}
		} else
			el->el_cursor.h = el->el_term.t_size.h - 1;
	}
}
