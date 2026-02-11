canSetAffiliation(const XMPP::MUCItem& i1, const XMPP::MUCItem& i2, XMPP::MUCItem::Affiliation a)
{
	if (i2.affiliation() == a)
		return true;

	if (!i2.jid().isValid())
		return false;

	if (a == MUCItem::Outcast) {
		return canBan(i1,i2);
	}
	else if (a == MUCItem::NoAffiliation) {
		return (i2.affiliation() >= MUCItem::Admin ? canRevokeAdmin(i1,i2) : canRevokeMember(i1,i2));
	}
	else if (a == MUCItem::Member) {
		return (i2.affiliation() >= MUCItem::Admin ? canRevokeAdmin(i1,i2) : canGrantMember(i1,i2));
	}
	else if (a == MUCItem::Admin) {
		return (i2.affiliation() == MUCItem::Owner ? canRevokeOwner(i1,i2) : canGrantAdmin(i1,i2));
	}
	else if (a == MUCItem::Owner) {
		return canGrantOwner(i1,i2);
	}

	return false;
}
