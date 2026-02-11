lex_(inbuf, outbuf, op, vbflag)
char *inbuf;
integer *outbuf;
integer *op;
logical vbflag;
{


    static const char dlimit[9] = { 'A', 'Z', 'A' - 1,
				    '1', '9', '1' - 31,
				    '-', '-', '-' - 27 };


    logical ret_val;


    integer i;
    char j;
    integer k, j1, j2, cp;


    --outbuf;
    --inbuf;


    for (i = 1; i <= 40; ++i) {

	outbuf[i] = 0;

    }

    ret_val = FALSE_;

    *op = -1;

L50:
    *op += 2;

    cp = 0;


L200:
    j = inbuf[prsvec_1.prscon];


    if (j == '\0')
	goto L1000;


    ++prsvec_1.prscon;


    if (j == '.') {
	goto L1000;
    }

    if (j == ',') {
	goto L1000;
    }

    if (j == ' ') {
	goto L6000;
    }

    for (i = 1; i <= 9; i += 3) {

	if (j >= dlimit[i - 1] & j <= dlimit[i]) {
	    goto L4000;
	}

    }

    if (vbflag) {
	rspeak_(601);
    }

    return ret_val;


L1000:
    if (inbuf[prsvec_1.prscon] == '\0') {
	prsvec_1.prscon = 1;
    }

    if (cp == 0 & *op == 1) {
	return ret_val;
    }
    if (cp == 0) {
	*op += -2;
    }

    ret_val = TRUE_;
    return ret_val;


L4000:
    j1 = j - dlimit[i + 1];
    if (cp >= 6) {
	goto L200;
    }

    k = *op + cp / 3;

    switch (cp % 3 + 1) {
	case 1:  goto L4100;
	case 2:  goto L4200;
	case 3:  goto L4300;
    }

L4100:
    j2 = j1 * 780;

    outbuf[k] = outbuf[k] + j2 + j2;

L4200:
    outbuf[k] += j1 * 39;

L4300:
    outbuf[k] += j1;

    ++cp;
    goto L200;


L6000:
    if (cp == 0) {
	goto L200;
    }

    goto L50;


}
