firstLocation(Location& loc) const
{
	if (root_.childCount() == 0)
		return false;

	loc = root_.child(0)->data().loc_;
	return true;
}
