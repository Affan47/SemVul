canRevokeAdmin(const XMPP::MUCItem& i1, const XMPP::MUCItem& i2)
{
	return i1.affiliation() >= MUCItem::Owner && i2.affiliation() == MUCItem::Admin && !i2.jid().isEmpty();
}
