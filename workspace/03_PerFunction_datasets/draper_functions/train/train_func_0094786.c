get(const DiscoItem &item)
{
	DiscoItem::Identity id;
	if ( item.identities().count() == 1 )
		id = item.identities().first();
	get(item.jid(), item.node(), id);
}
