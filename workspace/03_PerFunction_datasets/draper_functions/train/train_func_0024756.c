thisit_(oidx, aidx, obj, spcobj)
integer oidx;
integer aidx;
integer obj;
integer spcobj;
{


    const integer r50min = 1600;


    logical ret_val;


    integer i;

    ret_val = FALSE_;

    if (spcobj != 0 && obj == spcobj) {
	goto L500;
    }


    i = oidx + 1;
L100:
    ++i;
    if (ovoc[i - 1] <= 0 || ovoc[i - 1] >= r50min) {
	return ret_val;
    }

    if (ovoc[i - 1] != obj) {
	goto L100;
    }


    if (aidx == 0) {
	goto L500;
    }

    i = aidx + 1;
L200:
    ++i;
    if (avoc[i - 1] <= 0 || avoc[i - 1] >= r50min) {
	return ret_val;
    }

    if (avoc[i - 1] != obj) {
	goto L200;
    }


L500:
    ret_val = TRUE_;
    return ret_val;
}
