treedown(VOID_A)
{
	char *cp, *dir;
	int min, oy, otop;

	min = filetop(win);
	oy = tr_line;
	otop = tr_top;
	if (tr_line < tr_bottom - 1 && tr_line < min + FILEPERROW - 2)
		tr_line++;
	else if (tr_bottom >= min + FILEPERROW) tr_top--;
	else return(-1);
	searchtree();

	if (!tr_cur || !(tr_cur -> sub)) return(0);
	if (tr_cur -> sub[tr_no].max >= 0 || tr_cur -> sub[tr_no].name)
		return(0);

	waitmes();
	dir = treepath;
#ifdef	DEP_DOSPATH
	if (_dospath(treepath)) dir += 2;
#endif

	cp = strrdelim(dir, 0);
	if (cp == dir) cp++;
#ifdef	DOUBLESLASH
	else if (cp - treepath < isdslash(treepath)) cp++;
#endif
#ifdef	DEP_URLPATH
	else if (cp - treepath < _urlpath(treepath, NULL, NULL)) cp++;
#endif
	*cp = '\0';
	if (!expandtree(tr_cur)) {
		tr_line = oy;
		tr_top = otop;
		searchtree();
		return(-1);
	}
	searchtree();
	redraw = 1;

	return(0);
}
