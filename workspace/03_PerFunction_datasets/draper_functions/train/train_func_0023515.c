isaclone(ht_view *view)
{
	if (group) return group->isaclone(this);
	return 0;
}
