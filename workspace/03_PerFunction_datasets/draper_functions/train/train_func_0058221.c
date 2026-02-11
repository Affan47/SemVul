remove(const Jid &jid)
{
	type = 1;

	QDomElement item = doc()->createElement("item");
	item.setAttribute("jid", jid.full());
	item.setAttribute("subscription", "remove");
	d->itemList += item;
}
