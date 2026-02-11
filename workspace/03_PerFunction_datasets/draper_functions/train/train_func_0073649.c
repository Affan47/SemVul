asUPDATE(n)
Int n; {
    if (!newBasicBlock && instrAt(lastInstr)==iMKAP) {
	Int m = intAt(lastInstr+1);
	nextInstr(lastInstr);
	if (m==1)
	    instrInt(iUPDAP,n);
	else {
	    instrInt(iMKAP,m-1);
	    instrInt(iUPDAP,n);
	}
    }
    else
	instrInt(iUPDATE,n);
    srsp--;
}
