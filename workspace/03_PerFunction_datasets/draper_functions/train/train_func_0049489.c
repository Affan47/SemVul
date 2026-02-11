locationFromIndex(const QModelIndex& idx,
                                          Location& loc) const
{

	if (!idx.isValid())
		return false;


	int pos = idx.row();
	if (pos < 0 || pos >= locList_.size())
		return false;


	loc = locList_.at(pos);
	return true;
}
