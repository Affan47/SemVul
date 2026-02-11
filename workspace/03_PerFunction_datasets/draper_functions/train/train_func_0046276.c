Prologue(void)
{
    if (eflag) {
	floatish epsfscale = epsfwidth / (floatish) borderwidth;
	EPSFSpecialComments(epsfscale);
	Scaling(epsfscale);
    } else {
	StandardSpecialComments();
	if (gflag) Portrait(); else Landscape();
    }
}
