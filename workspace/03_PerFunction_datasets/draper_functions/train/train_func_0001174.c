dragDrop(const QString &text, ContactViewItem *i)
{
	if(!d->pa->loggedIn())
		return;


	ContactViewItem *gr;
	if(i->type() == ContactViewItem::Group)
		gr = i;
	else
		gr = (ContactViewItem *)static_cast<Q3ListViewItem *>(i)->parent();

	Jid j(text);
	if(!j.isValid())
		return;
	Entry *e = findEntry(j);
	if(!e)
		return;
	const UserListItem &u = e->u;
	QStringList gl = u.groups();


	if(gr->groupType() == ContactViewItem::gGeneral && gl.isEmpty())
		return;

	if(gr->groupType() == ContactViewItem::gUser && u.inGroup(gr->groupName()))
		return;


	for(QStringList::ConstIterator it = gl.begin(); it != gl.end(); ++it) {
		actionGroupRemove(u.jid(), *it);
	}
	if(gr->groupType() == ContactViewItem::gUser) {

		actionGroupAdd(u.jid(), gr->groupName());
	}
}
