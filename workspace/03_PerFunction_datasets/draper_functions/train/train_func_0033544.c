filterContact(ContactViewItem *item, bool refineSearch)
{
	if (!item) {
		return false;
	}
	if (item->type() != ContactViewItem::Contact) {
		return false;
	}
	if (filterString_.isNull()) {
		return true;
	}

	if (refineSearch && !item->isVisible()) {
		return false;
	}
	if (TextUtil::rich2plain(item->text(0)).contains(filterString_,Qt::CaseInsensitive))
	{
		ensureItemVisible(item);
		item->setVisible(true);
		item->optionsUpdate();
	}
	else
	{
		item->setVisible(false);
	}
	item->repaint();
	return item->isVisible();
}
