mvwinsch (WINDOW * a1, int a2, int a3, chtype z)
{
	T((T_CALLED("mvwinsch(%p,%d,%d,%s)"), a1, a2, a3, _tracechtype2(3,z))); returnCode((wmove(a1,a2,a3) == (-1) ? (-1) : winsch(a1,z)));
}
