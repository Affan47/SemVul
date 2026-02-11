mvdelch (int a1, int z)
{
	T((T_CALLED("mvdelch(%d,%d)"), a1, z)); returnCode((wmove(stdscr,a1,z) == (-1) ? (-1) : wdelch(stdscr)));
}
