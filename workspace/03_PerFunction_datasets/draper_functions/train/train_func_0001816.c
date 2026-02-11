parse_(inbuf, vbflag)
char *inbuf;
logical vbflag;
{

    integer i__1;
    logical ret_val;


    integer outbuf[40], outlnt;


    --inbuf;


    ret_val = FALSE_;

    prsvec_1.prsa = 0;

    prsvec_1.prsi = 0;
    prsvec_1.prso = 0;

    if (! lex_(inbuf + 1, outbuf, &outlnt, vbflag)) {
	goto L100;
    }
    if ((i__1 = sparse_(outbuf, outlnt, vbflag)) < 0) {
	goto L100;
    } else if (i__1 == 0) {
	goto L200;
    } else {
	goto L300;
    }


L200:
    if (! (vbflag)) {
	goto L350;
    }

    if (! synmch_()) {
	goto L100;
    }

    if (prsvec_1.prso > 0 & prsvec_1.prso < xsrch_1.xmin) {
	last_1.lastit = prsvec_1.prso;
    }


L300:
    ret_val = TRUE_;
L350:
    orphan_(0, 0, 0, 0, 0);

    return ret_val;


L100:
    prsvec_1.prscon = 1;
    return ret_val;

}
