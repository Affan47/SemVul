filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
	QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
	if (!idx.isValid())
		return false;

	if (!idx.parent().isValid())
		return true;

	if (filterRegExp().indexIn(idx.data().toString()) >= 0)
		return true;

	return false;
}
