update_topl(const char *bp)
{
	char *tl, *otl;
	int n0;
	int notdied = 1;
	struct WinDesc *cw = wins[WIN_MESSAGE];


	n0 = strlen(bp);
	if ((ttyDisplay->toplin == 1 || (cw->flags & WIN_STOP)) &&
	    cw->cury == 0 &&
	    n0 + (int)strlen(toplines) + 3 < CO-8 &&
	    (notdied = strncmp(bp, "You die", 7))) {
		strcat(toplines, "  ");
		strcat(toplines, bp);
		cw->curx += 2;
		if(!(cw->flags & WIN_STOP))
		    addtopl(bp);
		return;
	} else if (!(cw->flags & WIN_STOP)) {
	    if(ttyDisplay->toplin == 1) more();
	    else if(cw->cury) {
		docorner(1, cw->cury+1);
		cw->curx = cw->cury = 0;
	    }
	}
	remember_topl();
	(void) strncpy(toplines, bp, TBUFSZ);
	toplines[TBUFSZ - 1] = 0;

	for(tl = toplines; n0 >= CO; ){
	    otl = tl;
	    for(tl+=CO-1; tl != otl && !isspace(*tl); --tl) ;
	    if(tl == otl) {

		tl = index(otl, ' ');
		if (!tl) break;
	    }
	    *tl++ = '\n';
	    n0 = strlen(tl);
	}
	if(!notdied) cw->flags &= ~WIN_STOP;
	if(!(cw->flags & WIN_STOP)) redotoplin(toplines);
}
