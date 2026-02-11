index(int row, int column, const QModelIndex & parent) const
{

	Xmms2dPrefItem *parentItem;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<Xmms2dPrefItem*>(parent.internalPointer());

	Xmms2dPrefItem *childItem = parentItem->child(row);


	if (childItem) {

		return createIndex(row, column, childItem);
	}
	else {

		return QModelIndex();
	}
}
