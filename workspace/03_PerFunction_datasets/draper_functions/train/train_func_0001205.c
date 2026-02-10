doContext()
{
	ContactViewItem *i = (ContactViewItem *)selectedItem();
	if(!i)
		return;
	ensureItemVisible(i);

	if(i->type() == ContactViewItem::Group)
		setOpen(i, !i->isOpen());
	else
		qlv_contextPopup(i, viewport()->mapToGlobal(QPoint(32, itemPos(i))), 0);
}
