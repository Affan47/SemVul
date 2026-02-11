mvwaddnstr (WINDOW * a1, int a2, int a3, const char * a4, int z)
{
	T((T_CALLED("mvwaddnstr(%p,%d,%d,%s,%d)"), a1, a2, a3, _nc_visbuf2(3,a4), z)); returnCode((wmove(a1,a2,a3) == (-1) ? (-1) : waddnstr(a1,a4,z)));
}
