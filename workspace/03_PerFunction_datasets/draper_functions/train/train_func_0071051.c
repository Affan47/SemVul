GetRegion(int n)
{
	forlist(this) {
		if (((ARegion *) elem)->num == n) return ((ARegion *) elem);
	}
	return 0;
}
