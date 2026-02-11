plstrip_legend(PLStrip *mystripc, int first)
{
    int i;
    PLFLT sc, dy;


    plgchr(&sc, &dy);
    sc = dy = dy/100;
    plwind(-0.01, 1.01, -0.01, 1.01);
    for (i=0; i<PEN; i++) {
	if (mystripc->npts[i] || first) {
	    plcol(mystripc->colline[i]);
	    pllsty(mystripc->styline[i]);
	    pljoin(mystripc->xlpos, mystripc->ylpos - sc,
		   mystripc->xlpos + 0.1, mystripc->ylpos - sc);
	    plcol(mystripc->collab);
	    plptex(mystripc->xlpos + 0.11, mystripc->ylpos - sc,
		   0., 0., 0, mystripc->legline[i]);
	    sc += dy;
	}
    }
    plwind(mystripc->xmin, mystripc->xmax, mystripc->ymin, mystripc->ymax);
    plflush();
}
