setData(const QModelIndex& index, const QVariant& data, int role)
{
	if (!index.isValid())
		return false;

	ContactListItem* item = static_cast<ContactListItem*>(index.internalPointer());
	if (role == ContextMenuRole) {
		item->showContextMenu(data.toPoint());
	}

	return true;
}
