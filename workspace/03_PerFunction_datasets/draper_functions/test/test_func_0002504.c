getWatch(Literal p, Constraint* c) const {
	if (!validWatch(p)) return 0;
	const WatchList& pList = watches_[p.index()];
	WatchList::const_right_iterator it = std::find_if(pList.right_begin(), pList.right_end(), GenericWatch::EqConstraint(c));
	return it != pList.right_end()
		? &const_cast<GenericWatch&>(*it)
		: 0;
}
