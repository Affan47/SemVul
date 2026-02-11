doformat()
{

	dodojoin((long)nlines, TRUE, FALSE);


	coladvance(MAXCOL);
	while (curwin->w_cursor.col && isspace(gchar_cursor()))
		dec_cursor();
	curs_columns(FALSE);


	State = INSERT;
#ifdef KANJI
	insertchar(NUL, NUL);
#else
	insertchar(NUL);
#endif
	State = NORMAL;
	updateScreen(NOT_VALID);
}
