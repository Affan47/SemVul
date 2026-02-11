rowCount(const QModelIndex &parent) const
{
	ContactListGroupItem* parentItem;
	if (parent.isValid()) {
		ContactListItem* item = static_cast<ContactListItem*>(parent.internalPointer());
		parentItem = dynamic_cast<ContactListGroupItem*>(item);
	}
	else {
		parentItem = contactList_->rootItem();
	}

	return (parentItem ? parentItem->items() : 0);
}
