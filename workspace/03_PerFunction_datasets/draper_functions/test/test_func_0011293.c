pathbar(VOID_A)
{
#ifndef	_NOTRADLAYOUT
	if (istradlayout()) {
		Xlocate(0, TL_PATH);
		Xputterm(L_CLEAR);

		Xlocate(TC_PATH, TL_PATH);
		Xattrputs(TS_PATH, 1);
		cputstr(TD_PATH, fullpath);

		Xlocate(TC_MARK, TL_PATH);
		VOID_C XXcprintf("%<*d", TD_MARK, mark);
		Xattrputs(TS_MARK, 1);
# if	FD >= 3
		if (sizeunit) VOID_C XXcprintf("%>'*qd", TD_SIZE, marksize);
		else
# endif
		VOID_C XXcprintf("%<'*qd", TD_SIZE, marksize);

		Xtflush();
		return;
	}
#endif

	Xlocate(0, L_PATH);
	Xputterm(L_CLEAR);

	Xlocate(C_PATH, L_PATH);
	Xattrputs(S_PATH, 1);
	cputstr(D_PATH, fullpath);

	Xtflush();
}
