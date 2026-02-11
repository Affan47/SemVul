asRUPDATE() {
    if (!newBasicBlock && instrAt(lastInstr)==iMKAP) {
	Int m = intAt(lastInstr+1);
	nextInstr(lastInstr);
	if (m==1)
	    instrNone(iRUPDAP);
	else {
	    instrInt(iMKAP,m-1);
	    instrNone(iRUPDAP);
	}
    }
    else
	instrNone(iRUPDATE);
}
