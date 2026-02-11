addBreak(bool redraw, linestyle lsty, Fl_Color lcol)
{
    pointIterator pi, pii;


    pii = pointlist.end();
    --pii;

    if (!pii->isBreak()) {

	if (redraw) {


	    pii = pointlist.end();
	    --pii;
	    while ((!pii->isBreak()) && (pii != pointlist.begin()))
		--pii;

	    if (pii->isBreak())
		++pii;


	    pi = pii++;
	    while (pii !=  pointlist.end()) {
		dbgprintf("Adding a line joining A(%d, %d) to B(%d,%d)\n",
			  pi->x(), pi->y(),
			  pii->x(), pii->y()
			  );
		linelist.push_back(imline(pi->x(),
					  pi->y(),
					  pii->x(),
					  pii->y(),
					  lsty,
					  xorvalforlines,
                                          lcol));
		mainViewer->add(linelist.back());

		(linelist.back()).redraw();
		pi = pii++;
	    }


	}

        pointParams myparams;
	myparams.annotated = true;
        myparams.lsty = lsty;
        myparams.lcol = lcol;
	addPoint(-1,-1,WEIRD_CONSTANT, 0, 0, 0, 0, myparams);
	dbgprintf("Adding break with style=%d, colour=%d\n",
		  (int)lsty, (int)lcol);

	showlist();

	hasChanged = true;
    }

    return;
}
