parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	ItemT* item = indexData(index);
	if (item == NULL || item->parent() == &root_)
		return QModelIndex();

	return createIndex(item->parent()->index(), 0, (void*)item->parent());
}
