canGrantVoice(const XMPP::MUCItem& i1, const XMPP::MUCItem& i2)
{
	return i1.role() == MUCItem::Moderator && i2.role() < MUCItem::Participant;
}
