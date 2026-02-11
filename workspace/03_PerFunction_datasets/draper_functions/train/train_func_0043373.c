readbuf(char **buf)
{
        register LINE   *lp1;
        register LINE   *lp2;
        register BUFFER *bp;
        register WINDOW *wp;
        register int    i;
        register int    s;
        char   *sptr;
        int		nbytes;
        char            line[NLINE];
	CELL            ac;

	bp = curbp;
        bp->b_flag &= ~(BFTEMP|BFCHG);
	sptr = *buf;
	ac.a  = 0;

        while((s=sgetline(&sptr,&nbytes,line,NLINE)) == FIOSUC || s == FIOLNG){

                if ((lp1=lalloc(nbytes)) == NULL) {
                        s = FIOERR;
                        break;
                }
                lp2 = lback(curbp->b_linep);
                lp2->l_fp = lp1;
                lp1->l_fp = curbp->b_linep;
                lp1->l_bp = lp2;
                curbp->b_linep->l_bp = lp1;
                for (i=0; i<nbytes; ++i){
		    ac.c = line[i];
		    lputc(lp1, i, ac);
		}
        }

        for (wp=wheadp; wp!=NULL; wp=wp->w_wndp) {
                if (wp->w_bufp == curbp) {
                        wheadp->w_linep = lforw(curbp->b_linep);
                        wheadp->w_dotp  = lback(curbp->b_linep);
                        wheadp->w_doto  = 0;
                        wheadp->w_markp = NULL;
                        wheadp->w_marko = 0;
                        wheadp->w_flag |= WFHARD;
                }
        }

	strncpy(bp->b_bname, "main", sizeof(bp->b_bname));
	bp->b_bname[sizeof(bp->b_bname)-1] = '\0';
	strncpy(bp->b_fname, "", sizeof(bp->b_fname));
	bp->b_fname[sizeof(bp->b_fname)-1] = '\0';

	bp->b_dotp = bp->b_linep;
	bp->b_doto = 0;
}
