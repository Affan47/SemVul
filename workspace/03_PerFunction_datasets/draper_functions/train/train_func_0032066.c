MoveUp_svg(double *xcm, double *ycm)
{
#ifdef DEBUG
	printf("DEBUG(%s:%d) moving text position up one level.  Stack size on entry = %d\n", __FILE__,__LINE__,(int)pstack.size());
#endif
	if (!pstack.size())
		return;
	double dy;

	position p = pstack.top();
	if (p == Subscript) {


		gr_setfontsize_pt(gr_currentfontsize_pt() / SubSize);
		dy = SubMoveDown * gr_currentCapHeight_cm();
	} else {

		dy = SuperMoveUp * gr_currentCapHeight_cm();
		gr_setfontsize_pt(gr_currentfontsize_pt() * SuperSize);
	}
	*ycm += dy;
}
