removeRows(int row, int count, const QModelIndex &parent)
{
	beginRemoveRows(parent, row, row + count - 1);
	for(int i = 0; i < count; ++i)
	{
		mScript->removeAction(row);
	}
	endRemoveRows();

	return true;
}
