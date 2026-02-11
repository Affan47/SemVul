analyserenum_addrs(Location *locs, Address *at, Location *&loc)
{
	if ((at->compareTo(locs->addr) < 0) || !at->isValid()) {
		loc = locs;
		if (locs->left) analyserenum_addrs(locs->left, at, loc);
	} else  {
		if (locs->right) analyserenum_addrs(locs->right, at, loc);
	}
}
