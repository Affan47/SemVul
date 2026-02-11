unpack_(oldj, j)
integer oldj;
integer *j;
{

    integer i;

    for (i = 1; i <= 11; ++i) {

	syn[i - 1] = 0;

    }

    syntax_1.vflag = vvoc[oldj - 1];
    *j = oldj + 1;
    if ((syntax_1.vflag & SDIR) == 0) {
	return;
    }
    syntax_1.dfl1 = -1;

    syntax_1.dfl2 = -1;
    if ((syntax_1.vflag & SSTD) == 0) {
	goto L100;
    }
    syntax_1.dfw1 = -1;

    syntax_1.dfw2 = -1;
    syntax_1.dobj = VABIT + VRBIT + VFBIT;
    goto L200;

L100:
    syntax_1.dobj = vvoc[*j - 1];

    syntax_1.dfw1 = vvoc[*j];
    syntax_1.dfw2 = vvoc[*j + 1];
    *j += 3;
    if ((syntax_1.dobj & VEBIT) == 0) {
	goto L200;
    }
    syntax_1.dfl1 = syntax_1.dfw1;

    syntax_1.dfl2 = syntax_1.dfw2;

L200:
    if ((syntax_1.vflag & SIND) == 0) {
	return;
    }
    syntax_1.ifl1 = -1;

    syntax_1.ifl2 = -1;
    syntax_1.iobj = vvoc[*j - 1];
    syntax_1.ifw1 = vvoc[*j];
    syntax_1.ifw2 = vvoc[*j + 1];
    *j += 3;
    if ((syntax_1.iobj & VEBIT) == 0) {
	return;
    }
    syntax_1.ifl1 = syntax_1.ifw1;

    syntax_1.ifl2 = syntax_1.ifw2;
}
