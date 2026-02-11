gwim_(sflag, sfw1, sfw2)
integer sflag;
integer sfw1;
integer sfw2;
{

    integer ret_val;


    integer av;
    integer nobj, robj;
    logical nocare;


    ret_val = -1;

    av = advs_1.avehic[play_1.winner - 1];
    nobj = 0;
    nocare = (sflag & VCBIT) == 0;


    if ((sflag & VABIT) != 0) {
	nobj = fwim_(sfw1, sfw2, 0, 0, play_1.winner, nocare);
    }
    if ((sflag & VRBIT) != 0) {
	goto L100;
    }
L50:
    ret_val = nobj;
    return ret_val;


L100:
    robj = fwim_(sfw1, sfw2, play_1.here, 0, 0, nocare);
    if (robj < 0) {
	goto L500;
    } else if (robj == 0) {
	goto L50;
    } else {
	goto L200;
    }


L200:
    if (av == 0 || robj == av || (objcts_1.oflag2[robj - 1] & FINDBT)
	     != 0) {
	goto L300;
    }
    if (objcts_1.ocan[robj - 1] != av) {
	goto L50;
    }

L300:
    if (nobj != 0) {
	return ret_val;
    }

    if (! takeit_(robj, sflag)) {
	return ret_val;
    }

    ret_val = robj;
L500:
    return ret_val;

}
